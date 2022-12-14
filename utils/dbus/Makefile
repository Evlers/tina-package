#
# Copyright (C) 2007-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

# Make sure to also update the dbus-x package
PKG_NAME:=dbus
PKG_VERSION:=1.10.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://dbus.freedesktop.org/releases/dbus/
PKG_MD5SUM:=27b8e99ffad603b8acfa25201c6e3d5c
PKG_MAINTAINER:=Steven Barth <cyrus@openwrt.org>
PKG_LICENSE:=AFL-2.1

PKG_BUILD_PARALLEL:=1
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(BUILD_DIR)/host-build.mk
include $(BUILD_DIR)/package.mk

TARGET_LDFLAGS+= \
	-Wl,-rpath-link=$(OUT_DIR)/usr/lib \

define Package/dbus/Default
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Simple interprocess messaging system
  URL:=http://dbus.freedesktop.org/
endef

define Package/dbus/Default/description
 D-Bus is a message bus system, a simple way for applications to talk to one
 another. In addition to interprocess communication, D-Bus helps coordinate
 process lifecycle; it makes it simple and reliable to code a "single instance"
 application or daemon, and to launch applications and daemons on demand when
 their services are needed.
endef

define Package/libdbus
$(call Package/dbus/Default)
  CATEGORY:=Libraries
  TITLE+= (library)
  DEPENDS:= +libpthread
endef

define Package/libdbus/Description
$(call Package/dbus/Default/description)
 This package contains the D-Bus shared library.
endef

define Package/dbus
$(call Package/dbus/Default)
 TITLE+= (daemon)
 DEPENDS:= +libexpat +libdbus
endef

define Package/dbus/Description
$(call Package/dbus/Default/description)
 This package contains the D-Bus daemon.
endef

define Package/dbus-utils
$(call Package/dbus/Default)
 TITLE+= (utilities)
 DEPENDS:= dbus
endef

define Package/dbus-utils/Description
$(call Package/dbus/Default/description)
 This package contains D-Bus utilities.
endef


define Build/Prepare
	$(Build/Prepare/Default)
	$(SED) 's/-Wl,--gc-sections/--gc-sections/' $(PKG_BUILD_DIR)/configure
endef

CONFIGURE_ARGS += \
	--enable-shared \
	--enable-static \
	--enable-abstract-sockets \
	--disable-ansi \
	--disable-asserts \
	--disable-doxygen-docs \
	--disable-compiler_coverage \
	--disable-selinux \
	--disable-tests \
	--disable-verbose-mode \
	--disable-xml-docs \
	--with-xml="expat" \
	--with-dbus-user=root \
	--with-dbus-daemondir="/usr/sbin" \
	--with-system-socket="/var/run/dbus/system_bus_socket" \
	--with-system-pid-file="/var/run/dbus.pid" \
	--without-x \
	--libexecdir=/usr/lib/dbus-1

CONFIGURE_ARGS += \
	--disable-libaudit \
	--disable-libcap-ng

CONFIGURE_VARS+= \
	ac_cv_have_abstract_sockets="yes" \
	ac_cv_lib_expat_XML_ParserCreate_MM="yes" \

HOST_CONFIGURE_ARGS+= \
	--enable-shared \
	--enable-static \
	--enable-abstract-sockets \
	--disable-ansi \
	--disable-asserts \
	--disable-docygen-docs \
	--disable-compiler_coverage \
	--disable-selinux \
	--disable-tests \
	--disable-verbose-mode \
	--disable-xml-docs \
	--with-dbus-user=root \
	--with-dbus-daemondir="$(STAGING_DIR)/host/bin" \
	--with-system-socket="$(OUT_DIR)/host/var/run/dbus/system_bus_socket" \
	--with-system-pid-file="$(OUT_DIR)/host/var/run/dbus.pid" \
	--without-x \
	--libexecdir="$(OUT_DIR)/host/lib/dbus-1"

HOST_CONFIGURE_VARS+= \
	ac_cv_have_abstract_sockets="yes" \
	ac_cv_lib_expat_XML_ParserCreate_MM="yes" \

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/* \
		$(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/* \
		$(1)/usr/lib
endef

define Package/dbus/conffiles
/etc/dbus-1/session.conf
/etc/dbus-1/system.conf
endef

define Package/libdbus/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libdbus-1.so.* \
		$(1)/usr/lib/
endef

define Package/dbus/install
	$(INSTALL_DIR) $(1)/usr/share
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/share/dbus-1 \
		$(1)/usr/share/

	$(INSTALL_DIR) $(1)/usr/lib/dbus-1
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/lib/dbus-1/dbus-daemon-launch-helper \
		$(1)/usr/lib/dbus-1/

	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/sbin/dbus-daemon \
		$(1)/usr/sbin/

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/bin/dbus-uuidgen \
		$(1)/usr/bin/

	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/bin/dbus-launch \
		$(1)/usr/bin/dbus-launch.real
	$(INSTALL_BIN) \
		./files/dbus-launch \
		$(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) \
		./files/dbus.init \
		$(1)/etc/init.d/dbus
endef

define Package/dbus-utils/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/bin/dbus-{send,monitor,cleanup-sockets} \
		$(1)/usr/bin/
endef

$(eval $(call HostBuild))
$(eval $(call BuildPackage,libdbus))
$(eval $(call BuildPackage,dbus))
$(eval $(call BuildPackage,dbus-utils))
