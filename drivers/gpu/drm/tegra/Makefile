ccflags-$(CONFIG_DRM_TEGRA_DEBUG) += -DDEBUG

tegra-drm-y := \
	bus.o \
	drm.o \
	gem.o \
	fb.o \
	dc.o \
	output.o \
	rgb.o \
	hdmi.o \
	mipi-phy.o \
	dsi.o \
	sor.o \
	dpaux.o \
	gr2d.o \
	gr3d.o

tegra-drm-y += gk20a.o

obj-$(CONFIG_DRM_TEGRA) += tegra-drm.o
