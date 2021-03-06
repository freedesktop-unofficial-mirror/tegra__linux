/*
 * drivers/net/bond/bond_netlink.c - Netlink interface for bonding
 * Copyright (c) 2013 Jiri Pirko <jiri@resnulli.us>
 * Copyright (c) 2013 Scott Feldman <sfeldma@cumulusnetworks.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_link.h>
#include <linux/if_ether.h>
#include <net/netlink.h>
#include <net/rtnetlink.h>
#include <linux/reciprocal_div.h>
#include "bonding.h"

static const struct nla_policy bond_policy[IFLA_BOND_MAX + 1] = {
	[IFLA_BOND_MODE]		= { .type = NLA_U8 },
	[IFLA_BOND_ACTIVE_SLAVE]	= { .type = NLA_U32 },
	[IFLA_BOND_MIIMON]		= { .type = NLA_U32 },
	[IFLA_BOND_UPDELAY]		= { .type = NLA_U32 },
	[IFLA_BOND_DOWNDELAY]		= { .type = NLA_U32 },
	[IFLA_BOND_USE_CARRIER]		= { .type = NLA_U8 },
	[IFLA_BOND_ARP_INTERVAL]	= { .type = NLA_U32 },
	[IFLA_BOND_ARP_IP_TARGET]	= { .type = NLA_NESTED },
	[IFLA_BOND_ARP_VALIDATE]	= { .type = NLA_U32 },
	[IFLA_BOND_ARP_ALL_TARGETS]	= { .type = NLA_U32 },
	[IFLA_BOND_PRIMARY]		= { .type = NLA_U32 },
	[IFLA_BOND_PRIMARY_RESELECT]	= { .type = NLA_U8 },
	[IFLA_BOND_FAIL_OVER_MAC]	= { .type = NLA_U8 },
	[IFLA_BOND_XMIT_HASH_POLICY]	= { .type = NLA_U8 },
	[IFLA_BOND_RESEND_IGMP]		= { .type = NLA_U32 },
	[IFLA_BOND_NUM_PEER_NOTIF]	= { .type = NLA_U8 },
	[IFLA_BOND_ALL_SLAVES_ACTIVE]	= { .type = NLA_U8 },
	[IFLA_BOND_MIN_LINKS]		= { .type = NLA_U32 },
	[IFLA_BOND_LP_INTERVAL]		= { .type = NLA_U32 },
	[IFLA_BOND_PACKETS_PER_SLAVE]	= { .type = NLA_U32 },
	[IFLA_BOND_AD_LACP_RATE]	= { .type = NLA_U8 },
	[IFLA_BOND_AD_SELECT]		= { .type = NLA_U8 },
	[IFLA_BOND_AD_INFO]		= { .type = NLA_NESTED },
};

static int bond_validate(struct nlattr *tb[], struct nlattr *data[])
{
	if (tb[IFLA_ADDRESS]) {
		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			return -EINVAL;
		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			return -EADDRNOTAVAIL;
	}
	return 0;
}

static int bond_changelink(struct net_device *bond_dev,
			   struct nlattr *tb[], struct nlattr *data[])
{
	struct bonding *bond = netdev_priv(bond_dev);
	int miimon = 0;
	int err;

	if (!data)
		return 0;

	if (data[IFLA_BOND_MODE]) {
		int mode = nla_get_u8(data[IFLA_BOND_MODE]);

		err = bond_option_mode_set(bond, mode);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ACTIVE_SLAVE]) {
		int ifindex = nla_get_u32(data[IFLA_BOND_ACTIVE_SLAVE]);
		struct net_device *slave_dev;

		if (ifindex == 0) {
			slave_dev = NULL;
		} else {
			slave_dev = __dev_get_by_index(dev_net(bond_dev),
						       ifindex);
			if (!slave_dev)
				return -ENODEV;
		}
		err = bond_option_active_slave_set(bond, slave_dev);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_MIIMON]) {
		miimon = nla_get_u32(data[IFLA_BOND_MIIMON]);

		err = bond_option_miimon_set(bond, miimon);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_UPDELAY]) {
		int updelay = nla_get_u32(data[IFLA_BOND_UPDELAY]);

		err = bond_option_updelay_set(bond, updelay);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_DOWNDELAY]) {
		int downdelay = nla_get_u32(data[IFLA_BOND_DOWNDELAY]);

		err = bond_option_downdelay_set(bond, downdelay);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_USE_CARRIER]) {
		int use_carrier = nla_get_u8(data[IFLA_BOND_USE_CARRIER]);

		err = bond_option_use_carrier_set(bond, use_carrier);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ARP_INTERVAL]) {
		int arp_interval = nla_get_u32(data[IFLA_BOND_ARP_INTERVAL]);

		if (arp_interval && miimon) {
			pr_err("%s: ARP monitoring cannot be used with MII monitoring.\n",
			       bond->dev->name);
			return -EINVAL;
		}

		err = bond_option_arp_interval_set(bond, arp_interval);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ARP_IP_TARGET]) {
		__be32 targets[BOND_MAX_ARP_TARGETS] = { 0, };
		struct nlattr *attr;
		int i = 0, rem;

		nla_for_each_nested(attr, data[IFLA_BOND_ARP_IP_TARGET], rem) {
			__be32 target = nla_get_be32(attr);
			targets[i++] = target;
		}

		err = bond_option_arp_ip_targets_set(bond, targets, i);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ARP_VALIDATE]) {
		int arp_validate = nla_get_u32(data[IFLA_BOND_ARP_VALIDATE]);

		if (arp_validate && miimon) {
			pr_err("%s: ARP validating cannot be used with MII monitoring.\n",
			       bond->dev->name);
			return -EINVAL;
		}

		err = bond_option_arp_validate_set(bond, arp_validate);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ARP_ALL_TARGETS]) {
		int arp_all_targets =
			nla_get_u32(data[IFLA_BOND_ARP_ALL_TARGETS]);

		err = bond_option_arp_all_targets_set(bond, arp_all_targets);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_PRIMARY]) {
		int ifindex = nla_get_u32(data[IFLA_BOND_PRIMARY]);
		struct net_device *dev;
		char *primary = "";

		dev = __dev_get_by_index(dev_net(bond_dev), ifindex);
		if (dev)
			primary = dev->name;

		err = bond_option_primary_set(bond, primary);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_PRIMARY_RESELECT]) {
		int primary_reselect =
			nla_get_u8(data[IFLA_BOND_PRIMARY_RESELECT]);

		err = bond_option_primary_reselect_set(bond, primary_reselect);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_FAIL_OVER_MAC]) {
		int fail_over_mac =
			nla_get_u8(data[IFLA_BOND_FAIL_OVER_MAC]);

		err = bond_option_fail_over_mac_set(bond, fail_over_mac);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_XMIT_HASH_POLICY]) {
		int xmit_hash_policy =
			nla_get_u8(data[IFLA_BOND_XMIT_HASH_POLICY]);

		err = bond_option_xmit_hash_policy_set(bond, xmit_hash_policy);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_RESEND_IGMP]) {
		int resend_igmp =
			nla_get_u32(data[IFLA_BOND_RESEND_IGMP]);

		err = bond_option_resend_igmp_set(bond, resend_igmp);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_NUM_PEER_NOTIF]) {
		int num_peer_notif =
			nla_get_u8(data[IFLA_BOND_NUM_PEER_NOTIF]);

		err = bond_option_num_peer_notif_set(bond, num_peer_notif);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_ALL_SLAVES_ACTIVE]) {
		int all_slaves_active =
			nla_get_u8(data[IFLA_BOND_ALL_SLAVES_ACTIVE]);

		err = bond_option_all_slaves_active_set(bond,
							all_slaves_active);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_MIN_LINKS]) {
		int min_links =
			nla_get_u32(data[IFLA_BOND_MIN_LINKS]);

		err = bond_option_min_links_set(bond, min_links);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_LP_INTERVAL]) {
		int lp_interval =
			nla_get_u32(data[IFLA_BOND_LP_INTERVAL]);

		err = bond_option_lp_interval_set(bond, lp_interval);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_PACKETS_PER_SLAVE]) {
		int packets_per_slave =
			nla_get_u32(data[IFLA_BOND_PACKETS_PER_SLAVE]);

		err = bond_option_packets_per_slave_set(bond,
							packets_per_slave);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_AD_LACP_RATE]) {
		int lacp_rate =
			nla_get_u8(data[IFLA_BOND_AD_LACP_RATE]);

		err = bond_option_lacp_rate_set(bond, lacp_rate);
		if (err)
			return err;
	}
	if (data[IFLA_BOND_AD_SELECT]) {
		int ad_select =
			nla_get_u8(data[IFLA_BOND_AD_SELECT]);

		err = bond_option_ad_select_set(bond, ad_select);
		if (err)
			return err;
	}
	return 0;
}

static int bond_newlink(struct net *src_net, struct net_device *bond_dev,
			struct nlattr *tb[], struct nlattr *data[])
{
	int err;

	err = bond_changelink(bond_dev, tb, data);
	if (err < 0)
		return err;

	return register_netdevice(bond_dev);
}

static size_t bond_get_size(const struct net_device *bond_dev)
{
	return nla_total_size(sizeof(u8)) +	/* IFLA_BOND_MODE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ACTIVE_SLAVE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_MIIMON */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_UPDELAY */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_DOWNDELAY */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_USE_CARRIER */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_INTERVAL */
						/* IFLA_BOND_ARP_IP_TARGET */
		nla_total_size(sizeof(struct nlattr)) +
		nla_total_size(sizeof(u32)) * BOND_MAX_ARP_TARGETS +
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_VALIDATE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_ARP_ALL_TARGETS */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_PRIMARY */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_PRIMARY_RESELECT */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_FAIL_OVER_MAC */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_XMIT_HASH_POLICY */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_RESEND_IGMP */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_NUM_PEER_NOTIF */
		nla_total_size(sizeof(u8)) +   /* IFLA_BOND_ALL_SLAVES_ACTIVE */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_MIN_LINKS */
		nla_total_size(sizeof(u32)) +	/* IFLA_BOND_LP_INTERVAL */
		nla_total_size(sizeof(u32)) +  /* IFLA_BOND_PACKETS_PER_SLAVE */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_AD_LACP_RATE */
		nla_total_size(sizeof(u8)) +	/* IFLA_BOND_AD_SELECT */
		nla_total_size(sizeof(struct nlattr)) + /* IFLA_BOND_AD_INFO */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_AGGREGATOR */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_NUM_PORTS */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_ACTOR_KEY */
		nla_total_size(sizeof(u16)) + /* IFLA_BOND_AD_INFO_PARTNER_KEY*/
		nla_total_size(ETH_ALEN) +    /* IFLA_BOND_AD_INFO_PARTNER_MAC*/
		0;
}

static int bond_fill_info(struct sk_buff *skb,
			  const struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct net_device *slave_dev = bond_option_active_slave_get(bond);
	struct nlattr *targets;
	unsigned int packets_per_slave;
	int i, targets_added;

	if (nla_put_u8(skb, IFLA_BOND_MODE, bond->params.mode))
		goto nla_put_failure;

	if (slave_dev &&
	    nla_put_u32(skb, IFLA_BOND_ACTIVE_SLAVE, slave_dev->ifindex))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_MIIMON, bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_UPDELAY,
			bond->params.updelay * bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_DOWNDELAY,
			bond->params.downdelay * bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_USE_CARRIER, bond->params.use_carrier))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_ARP_INTERVAL, bond->params.arp_interval))
		goto nla_put_failure;

	targets = nla_nest_start(skb, IFLA_BOND_ARP_IP_TARGET);
	if (!targets)
		goto nla_put_failure;

	targets_added = 0;
	for (i = 0; i < BOND_MAX_ARP_TARGETS; i++) {
		if (bond->params.arp_targets[i]) {
			nla_put_be32(skb, i, bond->params.arp_targets[i]);
			targets_added = 1;
		}
	}

	if (targets_added)
		nla_nest_end(skb, targets);
	else
		nla_nest_cancel(skb, targets);

	if (nla_put_u32(skb, IFLA_BOND_ARP_VALIDATE, bond->params.arp_validate))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_ARP_ALL_TARGETS,
			bond->params.arp_all_targets))
		goto nla_put_failure;

	if (bond->primary_slave &&
	    nla_put_u32(skb, IFLA_BOND_PRIMARY,
			bond->primary_slave->dev->ifindex))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_PRIMARY_RESELECT,
		       bond->params.primary_reselect))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_FAIL_OVER_MAC,
		       bond->params.fail_over_mac))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_XMIT_HASH_POLICY,
		       bond->params.xmit_policy))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_RESEND_IGMP,
		        bond->params.resend_igmp))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_NUM_PEER_NOTIF,
		       bond->params.num_peer_notif))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_ALL_SLAVES_ACTIVE,
		       bond->params.all_slaves_active))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_MIN_LINKS,
			bond->params.min_links))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_LP_INTERVAL,
			bond->params.lp_interval))
		goto nla_put_failure;

	packets_per_slave = bond->params.packets_per_slave;
	if (packets_per_slave > 1)
		packets_per_slave = reciprocal_value(packets_per_slave);

	if (nla_put_u32(skb, IFLA_BOND_PACKETS_PER_SLAVE,
			packets_per_slave))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_AD_LACP_RATE,
		       bond->params.lacp_fast))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_AD_SELECT,
		       bond->params.ad_select))
		goto nla_put_failure;

	if (bond->params.mode == BOND_MODE_8023AD) {
		struct ad_info info;

		if (!bond_3ad_get_active_agg_info(bond, &info)) {
			struct nlattr *nest;

			nest = nla_nest_start(skb, IFLA_BOND_AD_INFO);
			if (!nest)
				goto nla_put_failure;

			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_AGGREGATOR,
					info.aggregator_id))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_NUM_PORTS,
					info.ports))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_ACTOR_KEY,
					info.actor_key))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_PARTNER_KEY,
					info.partner_key))
				goto nla_put_failure;
			if (nla_put(skb, IFLA_BOND_AD_INFO_PARTNER_MAC,
				    sizeof(info.partner_system),
				    &info.partner_system))
				goto nla_put_failure;

			nla_nest_end(skb, nest);
		}
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}

struct rtnl_link_ops bond_link_ops __read_mostly = {
	.kind			= "bond",
	.priv_size		= sizeof(struct bonding),
	.setup			= bond_setup,
	.maxtype		= IFLA_BOND_MAX,
	.policy			= bond_policy,
	.validate		= bond_validate,
	.newlink		= bond_newlink,
	.changelink		= bond_changelink,
	.get_size		= bond_get_size,
	.fill_info		= bond_fill_info,
	.get_num_tx_queues	= bond_get_num_tx_queues,
	.get_num_rx_queues	= bond_get_num_tx_queues, /* Use the same number
							     as for TX queues */
};

int __init bond_netlink_init(void)
{
	return rtnl_link_register(&bond_link_ops);
}

void bond_netlink_fini(void)
{
	rtnl_link_unregister(&bond_link_ops);
}

MODULE_ALIAS_RTNL_LINK("bond");
