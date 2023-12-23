#ifndef MACOSFIREWALL_H
#define MACOSFIREWALL_H

#include <QString>
#include <QStringList>

// Descriptor for a set of firewall rules to be appled.
//
struct FirewallParams
{
    QStringList dnsServers;
    //    QSharedPointer<NetworkAdapter> adapter;
    QVector<QString> excludeApps; // Apps to exclude if VPN exemptions are enabled

    QStringList allowAddrs;
    QStringList blockAddrs;

    // The follow flags indicate which general rulesets are needed. Note that
    // this is after some sanity filtering, i.e. an allow rule may be listed
    // as not needed if there were no block rules preceding it. The rulesets
    // should be thought of as in last-match order.

    bool blockAll;      // Block all traffic by default
    bool blockNets;
    bool allowNets;
    bool allowVPN;      // Exempt traffic through VPN tunnel
    bool allowDHCP;     // Exempt DHCP traffic
    bool blockIPv6;     // Block all IPv6 traffic
    bool allowLAN;      // Exempt LAN traffic, including IPv6 LAN traffic
    bool blockDNS;      // Block all DNS traffic except specified DNS servers
    bool allowPIA;      // Exempt PIA executables
    bool allowLoopback; // Exempt loopback traffic
    bool allowHnsd;     // Exempt Handshake DNS traffic
    bool allowVpnExemptions; // Exempt specified traffic from the tunnel (route it over the physical uplink instead)
};

// TODO: Break out firewall handling to a base class that can be used directly
// by the base daemon class, for some common functionality.

class MacOSFirewall
{

private:
    static int execute(const QString &command, bool ignoreErrors = false);
    static bool isPFEnabled();
    static bool isRootAnchorLoaded();

public:
    static void install();
    static void uninstall();
    static bool isInstalled();
    static void enableAnchor(const QString &anchor);
    static void disableAnchor(const QString &anchor);
    static bool isAnchorEnabled(const QString &anchor);
    static void setAnchorEnabled(const QString &anchor, bool enable);
    static void setAnchorTable(const QString &anchor, bool enabled, const QString &table, const QStringList &items);
    static void setAnchorWithRules(const QString &anchor, bool enabled, const QStringList &rules);
    static void ensureRootAnchorPriority();
    static void installRootAnchors();
};


#endif // MACOSFIREWALL_H
