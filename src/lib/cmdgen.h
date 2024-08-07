/* SPDX-License-Identifier: AGPL-3.0-or-later */
#ifndef IPROUTE2_SYSREPO_CMDGEN_H
#define IPROUTE2_SYSREPO_CMDGEN_H

#include <libyang/libyang.h>
#include <sysrepo.h>
#include <bsd/string.h>

#define CMDS_ARRAY_SIZE 1024
#define CMD_LINE_SIZE 1024

/**
 * @brief data struct to store command information.
 */
struct cmd_info {
    int argc;
    char **argv;
    int rollback_argc;
    char **rollback_argv;
};

/**
 * free the all the cmd_info.
 * @param cmds_info array of cmd_info struct.
 */
void free_cmds_info(struct cmd_info **cmds_info);

/**
 * FOR_OPER: parse the command line and convert it to argc, argv
 * @param [in]  command command line string "ip link add ..."
 * @param [out] argc parsed argv count
 * @param [out] argv parsed argv
 */
void parse_command(const char *command, int *argc, char ***argv);

/**
 * FOR_OPER: this func insert the netns name in the cmd, for example if cmd = ip link, and netns = "red"
 * the cmd will become "ip -n red link",
 * @param cmd
 * @param netns
 */
void insert_netns(char *cmd, const char *netns);

/**
 * @brief generate list of commands info from the lyd_node (diff).
 *
 *
 * @param[in] all_change_nodes lyd_node change data for all modules.
 * @return cmd_info array.
 */
struct cmd_info **lyd2cmds(const struct lyd_node *all_change_nodes);

#endif // IPROUTE2_SYSREPO_CMDGEN_H
