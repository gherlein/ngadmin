
/**
 * User interface file. 
 * All client applications which want to use NgAdmin must include this file. 
 * @file ngadmin.h
 */


#ifndef DEF_NGADMIN
#define DEF_NGADMIN


#include <stdbool.h>
#include <arpa/inet.h>
#include <netinet/ether.h>


#ifdef BUILD_LIB
#define EXPORT	__attribute__((visibility("default")))
#else
#define EXPORT	
#endif



/**
 * Maximum size of product string. 
 */
#define PRODUCT_SIZE	64

/**
 * Maximum size of name string. 
 **/
#define NAME_SIZE	64

/**
 *  Maximum size of firmware version string. 
 **/
#define FIRMWARE_SIZE	64



/**
 * Error codes. 
 * This enum lists all the error codes the library can return to user. 
 **/
enum {
 ERR_OK=0, 			/**< no error */
 ERR_NET=-1, 			/**< network error */
 ERR_NOTLOG=-2, 		/**< not logged */
 ERR_BADPASS=-3, 		/**< bad password */
 ERR_BADID=-4, 			/**< bad switch id */
 ERR_INVARG=-5, 		/**< invalid argument */
 ERR_TIMEOUT=-6, 		/**< timeout */
 ERR_NOTIMPL=-7			/**< not implemented */
};



/**
 * Port speeds. 
 * This enum lists all the speeds a port can have. 
 **/
enum {
 SPEED_DOWN=0, 			/**< link down */
 SPEED_10=1, 			/**< 10 Mb/s */
 SPEED_100=4, 			/**< 100 Mb/s */
 SPEED_1000=5			/**< 1000 Mb/s */
};



/**
 * VLAN types. 
 * This enum lists all the VLAN types available
 **/
enum {
 VLAN_DISABLED=0, 		/**< VLAN disabled */
 VLAN_PORT_BASIC=1, 		/**< port basic */
 VLAN_PORT_ADV=2, 		/**< port advanced */
 VLAN_DOT_BASIC=3, 		/**< 802.1q basic */
 VLAN_DOT_ADV=4			/**< 802.1q advanced */
};


/**
 * VLAN port specification. 
 * This enum lists all the VLAN specifications a port can have. 
 **/
enum {
 VLAN_UNSPEC=0xFF, 		/**< unspecified */
 VLAN_NO=0, 			/**< not present */
 VLAN_UNTAGGED=1, 		/**< present, untagged */
 VLAN_TAGGED=2			/**< present, tagged */
};



/**
 * Minimum VLAN id. 
 **/
#define VLAN_MIN		1

/**
 * Maximum VLAN id. 
 **/
#define VLAN_MAX		4093



/**
 * QoS modes. 
 * This enum lists all the availables QoS modes. 
 **/
enum {
 QOS_PORT=1, 			/**< port based */
 QOS_DOT=2			/**< 802.1p based */
};


/**
 * Port priorities. 
 * This enum lists all the priorities a port can have. 
 **/
enum {
 PRIO_UNSPEC=-1, 		/**< unspecified */
 PRIO_HIGH=1, 			/**< high */
 PRIO_MED=2, 			/**< medium */
 PRIO_NORM=3, 			/**< normal */
 PRIO_LOW=4			/**< low */
};




/**
 * Bitrates. 
 * This enum lists all the available bitrates. 
 **/
enum {
 BITRATE_UNSPEC=-1,	/**< unspecified */
 BITRATE_NOLIMIT=0,	/**< unlimited */ 
 BITRATE_512K=1, 	/**< 512 Kb/s */
 BITRATE_1M=2, 		/**< 1 Mb/s */
 BITRATE_2M=3, 		/**< 2 Mb/s */
 BITRATE_4M=4, 		/**< 4 Mb/s */
 BITRATE_8M=5, 		/**< 8 Mb/s */
 BITRATE_16M=6, 	/**< 16 Mb/s */
 BITRATE_32M=7, 	/**< 32 Mb/s */
 BITRATE_64M=8, 	/**< 64 Mb/s */
 BITRATE_128M=9, 	/**< 128 Mb/s */
 BITRATE_256M=10, 	/**< 256 Mb/s */
 BITRATE_512M=11	/**< 512 Mb/s */
};




/**
 * NgAdmin library main structure. 
 * The structure content is hidden to clients to prevent them to manually 
 * change data and mess up things. 
 **/
struct ngadmin;



/**
 * Network configuration. 
 * Represents the network configuration of a switch. 
 */
struct net_conf {
 struct in_addr ip;		/**< IP */
 struct in_addr netmask;	/**< netmask */
 struct in_addr gw;		/**< gateway IP */
 bool dhcp;			/**< DHCP enabled */
};


/**
 * Switch characteristics. 
 * Represents the main characteristics of a switch. 
 */
struct swi_attr {
 char product[PRODUCT_SIZE];	/**< product name (eg.\ GS108EV1) */
 char name[NAME_SIZE];		/**< custom name */
 char firmware[FIRMWARE_SIZE];	/**< firmware version string */
 unsigned char ports;		/**< number of ports */
 struct ether_addr mac;		/**< MAC address */
 struct net_conf nc;		/**< network configuration */
};


/**
 * Port statistics. 
 * Represents statistics of a particular port. 
 */
struct port_stats {
 unsigned long long recv;	/**< packets received */
 unsigned long long sent;	/**< packets sent */
 unsigned long long crc;	/**< CRC errors */
};


/**
 * IGMP snooping configuration. 
 * Represents the IGMP snooping configuration of a switch. 
 */
struct igmp_conf {
 bool enable;			/**< IGMP snooping enabled */
 unsigned short vlan;		/**< VLAN on which IGMP snooping is done */
 bool validate;			/**< validate IGMPv3 headers */
 bool block;			/**< block unknown multicast addresses */
};


/**
 * Cabletest result.
 */
struct cabletest {
 char port;			/**< port */
 int v1;			/**< raw value 1 */
 int v2;			/**< raw value 2 */
};



#ifdef __cplusplus
extern "C" {
#endif


/**
 * Initialize NgAdmin library. 
 * This function initializes the NgAdmin library. You must call it before any 
 * other function. 
 * @param iface The network interface to use. 
 * @return A pointer to a ngadmin structure, or NULL if an error occurred. 
 */
struct ngadmin* ngadmin_init (const char *iface) EXPORT;


/**
 * Close NgAdmin library. 
 * This function frees the resources used by the library. You really should 
 * call this when you are done using the library. 
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 */
int ngadmin_close (struct ngadmin *nga) EXPORT;


/**
 * Force the use of the interface. 
 * This function allows to solve two problems: 
 * - When you have multiple network interfaces, sending to the broadcast may not 
 *   send the packet on the interface you want. \n
 *   This function forces the packet to go on the interface you specified at 
 *   the library initialization. 
 * - When the switch is not in your network range, because DHCP is disabled or
 *   you started the DHCP server after the switch. \n
 *   This function allows you to ignore the routing table and consider every 
 *   address is directly reachable on the interface. \n
 *   An alternative is to use ngadmin_setKeepBroadcasting. 
 * 
 * @warning Requires root priviledges. 
 * @see ngadmin_setKeepBroadcasting()
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 */
int ngadmin_forceInterface (struct ngadmin *nga) EXPORT;


/**
 * Keep broadcasting even when talking with a particular switch. 
 * By default, once you login on a switch, NgAdmin talks with it using unicast. 
 * This prevents the password from being sent to all your network. \n
 * The switch still replies using broadcast, but the password is not included 
 * in the replies. \n
 * This function allows you to disable this feature and do like the official 
 * Windows application that always use broadcast packets. \n
 * This also allows to configure a switch which is not on your network range 
 * without forcing the interface. \n
 * When you enable this option, you must be aware that on every parameter 
 * change you make on the switch, your password is broadcasted in cleartext 
 * to all your network. 
 * @see ngadmin_forceInterface()
 * @param nga A pointer to the ngadmin structure. 
 * @param value Enable or disable the systematic use of broadcast packets. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setKeepBroadcasting (struct ngadmin *nga, bool value) EXPORT;


/**
 * Specify the password to use to login. 
 * Sets the password to use to login on switches. 
 * @param nga A pointer to the ngadmin structure. 
 * @param pass The password string to use. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setPassword (struct ngadmin *nga, const char *pass) EXPORT;


/**
 * Set timeout for networking. 
 * Sets the timeout when waiting for network packets. 
 * @param nga A pointer to the ngadmin structure. 
 * @param tv A pointer to a timeval structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setTimeout (struct ngadmin *nga, const struct timeval *tv) EXPORT;


/**
 * Scan the network for switches. 
 * This function scans the network for Netgear switches that use NSDP. 
 * @warning Systematically blocks for the timeout value. 
 * @note If you are logged on a switch, calling this function will delog you. 
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_scan (struct ngadmin *nga) EXPORT;


/**
 * Get the list of detected switches. 
 * This function allows you gou get the list of all last detected switchs. 
 * @note When a scan is done, this array is no more valid. 
 * @param nga A pointer to the ngadmin structure. 
 * @param nb A pointer to an integer which will receive the number of switches. 
 * @return A pointer to an array of switch characteristics. 
 */
const struct swi_attr* ngadmin_getSwitchTab (struct ngadmin *nga, int *nb) EXPORT;


/**
 * Get the switch on which you are logged. 
 * This function allows you to get the switch on which you are logged. 
 * @param nga A pointer to the ngadmin structure. 
 * @return A pointer the switch characteristics or NULL if you are not logged. 
 **/
const struct swi_attr* ngadmin_getCurrentSwitch (struct ngadmin *nga) EXPORT;


/**
 * Login on a switch. 
 * This function permits to login on a switch. 
 * @note If you are already logged, this function delogs you whatever the new 
 *       login attempt is successfull or not. 
 * @see ngadmin_setPassword()
 * @param nga A pointer to the ngadmin structure. 
 * @param id The id (position in the switch array) of the switch you want to login to. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_login (struct ngadmin *nga, int id) EXPORT;


/**
 * Get the ports speed status. 
 * This functions retrieves the ports speed status. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of ports which will receive ports status. 
 *         Must not be NULL. The array size must be ports_count*sizeof(unsigned char). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getPortsStatus (struct ngadmin *nga, unsigned char *ports) EXPORT;


/**
 * Change the name of a switch. 
 * This changes the name of a switch. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param name The name string to use. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setName (struct ngadmin *nga, const char *name) EXPORT;


/**
 * Get the ports statistics. 
 * Retrieves the ports packet statistics. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ps A pointer to an array of port_stats structures. Must not be NULL. 
 *        The array size must be ports_count*sizeof(struct port_stats). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getPortsStatistics (struct ngadmin *nga, struct port_stats *ps) EXPORT;


/**
 * Reset the ports statistics. 
 * This resets the ports packet statistics. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_resetPortsStatistics (struct ngadmin *nga) EXPORT;


/**
 * Change the password of a switch. 
 * This changes the password of a switch. On success, automatically updates 
 * local password so you do not have to relog. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param pass The new password string to use. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_changePassword (struct ngadmin *nga, const char* pass) EXPORT;


/**
 * Get the broadcast storm filtering state. 
 * Retrieves the broadcast storm filtering state. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param s A pointer to an integer which will receive 0 or 1. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getStormFilterState (struct ngadmin *nga, int *s) EXPORT;


/**
 * Set the broadcast storm filtering state. 
 * Changes the broadcast storm filtering state. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param s An integer with value 0 or 1. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setStormFilterState (struct ngadmin *nga, int s) EXPORT;


/**
 * Get the broadcast storm bitrates. 
 * Retrieves the broadcast storm filtering bitrates. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of integers. Must not be NULL. 
 *              The array size must be ports_count*sizeof(int). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getStormFilterValues (struct ngadmin *nga, int *ports) EXPORT;


/**
 * Set the broadcast storm bitrates. 
 * Changes the broadcast storm filtering values. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of integers. Must not be NULL. 
 *              The array size must be ports_count*sizeof(int). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setStormFilterValues (struct ngadmin *nga, const int *ports) EXPORT;


/**
 * Get the bitrates limits. 
 * Retrieves the bitrates limits of each port. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of integers. Must not be NULL. 
 *              The array size must be ports_count*sizeof(int). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getBitrateLimits (struct ngadmin *nga, int *ports) EXPORT;


/**
 * Set the bitrates limits. 
 * Changes the bitrates limits of each port. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of integers. Must not be NULL. 
 *              The array size must be ports_count*sizeof(int). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setBitrateLimits (struct ngadmin *nga, const int *ports) EXPORT;


/**
 * Get the QoS mode. 
 * Retrieve the QoS mode. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param s A pointer to an integer. Must not be NULL. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getQOSMode (struct ngadmin *nga, int *s) EXPORT;


/**
 * Set the QoS mode. 
 * Changes the QoS mode. 
 * @note You must be logged on a switch. 
 * @param nga A pointer to the ngadmin structure. 
 * @param s An integer with the new mode. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setQOSMode (struct ngadmin *nga, int s) EXPORT;


/**
 * Get the QoS values. 
 * Retrieve the QoS priority values for all the ports. 
 * @note You must be logged on a switch. 
 * @note The switch QoS mode should be port based to use this function. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of chars. Must not be NULL.
                The array size must be ports_count*sizeof(ports). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getQOSValues (struct ngadmin *nga, char *ports) EXPORT;


/**
 * Set the QoS values. 
 * Changes the QoS priority values for all the ports. 
 * @note You must be logged on a switch. 
 * @note The switch QoS mode should be port based to use this function. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of chars. Must not be NULL.
                The array size must be ports_count*sizeof(ports). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setQOSValues (struct ngadmin *nga, const char *ports) EXPORT;


/**
 * Restart the switch. 
 * Restarts the switch. 
 * @note You must be logged on a switch. 
 * @note If successfull, you should wait a few seconds while the switch 
         effectively restarts. 
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_restart (struct ngadmin *nga) EXPORT;


/**
 * Restore the switch default parameters. 
 * Restores the switch default parameters and restarts it. 
 * @note You must be logged on a switch. 
 * @note If successfull, you will be delogged and the switch list will be 
         cleared. You should wait a few seconds while the switch effectively restarts. 
 * @param nga A pointer to the ngadmin structure. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_defaults (struct ngadmin *nga) EXPORT;


/**
 * Get the port mirroring values. 
 * Retrieves the port mirrorring values. 
 * @note The switch QoS mode should be port based to use this function. 
 * @param nga A pointer to the ngadmin structure.
 * @param ports A pointer to an array of chars. Must not be NULL. \n
                The first element of the array is the output port (or 0 if port 
                mirroring is disabled), followed by 0 or 1 values for each port 
                if it is present or not. \n
                The array size must be (1+ports_count)*sizeof(char). 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_getMirror (struct ngadmin *nga, char *ports) EXPORT;


/**
 * Set the port mirroring values. 
 * Changes the port mirroring values. 
 * @note The switch QoS mode should be port based to use this function. 
 * @param nga A pointer to the ngadmin structure. 
 * @param ports A pointer to an array of chars. It as the same format as in 
                ngadmin_getMirror. \n
                If it is NULL, port mirroring is disabled. 
 * @return ERR_OK when everything is well or an error code otherwise. 
 **/
int ngadmin_setMirror (struct ngadmin *nga, const char *ports) EXPORT;


// 
int ngadmin_getIGMPConf (struct ngadmin *nga, struct igmp_conf *ic) EXPORT;


// 
int ngadmin_setIGMPConf (struct ngadmin *nga, const struct igmp_conf *ic) EXPORT;


// 
int ngadmin_cabletest (struct ngadmin *nga, struct cabletest *ct, int nb) EXPORT;


// 
int ngadmin_setNetConf (struct ngadmin *nga, const struct net_conf *nc) EXPORT;


// 
int ngadmin_getVLANType (struct ngadmin *nga, int *t) EXPORT;


// 
int ngadmin_setVLANType (struct ngadmin *nga, int t) EXPORT;


// 
int ngadmin_getVLANDotAllConf (struct ngadmin *nga, unsigned short *vlans, unsigned char *ports, int *nb) EXPORT;


// 
int ngadmin_getVLANDotConf (struct ngadmin *nga, unsigned short vlan, unsigned char *ports) EXPORT;


// 
int ngadmin_setVLANDotConf (struct ngadmin *nga, unsigned short vlan, const unsigned char *ports) EXPORT;


// 
int ngadmin_VLANDestroy (struct ngadmin *nga, unsigned short vlan) EXPORT;


// 
int ngadmin_getAllPVID (struct ngadmin *nga, unsigned short *ports) EXPORT;


// 
int ngadmin_setPVID (struct ngadmin *nga, unsigned char port, unsigned short vlan) EXPORT;


#ifdef __cplusplus
}
#endif



#endif

