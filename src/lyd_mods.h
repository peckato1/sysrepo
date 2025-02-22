/**
 * @file lyd_mods.h
 * @author Michal Vasko <mvasko@cesnet.cz>
 * @brief header for sysrepo module data routines
 *
 * @copyright
 * Copyright (c) 2018 - 2021 Deutsche Telekom AG.
 * Copyright (c) 2018 - 2021 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef _LYD_MODS_H
#define _LYD_MODS_H

#include <pthread.h>

#include <libyang/libyang.h>

#include "shm_types.h"
#include "sysrepo_types.h"

/**
 * @brief Parse internal module data.
 *
 * @param[in] ly_ctx Context to use for parsing SR data.
 * @param[in] allow_ctx_change Allow @p ly_ctx to be initialized with the internal modules, if not already.
 * @param[out] sr_mods_p Sysrepo module data tree.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_parse(const struct ly_ctx *ly_ctx, int allow_ctx_change, struct lyd_node **sr_mods_p);

/**
 * @brief Add a module to SR internal module data.
 *
 * @param[in] ly_ctx Context to use for parsing SR data.
 * @param[in] ly_mod Module that was added.
 * @param[in] module_ds Datastore implementation plugin name for each config datastore.
 * @param[in,out] mod_set Set of all the newly installed modules.
 * @param[out] sr_mods SR internal module data.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_change_add_module(const struct ly_ctx *ly_ctx, const struct lys_module *ly_mod,
        const sr_module_ds_t *module_ds, struct ly_set *mod_set, struct lyd_node **sr_mods);

/**
 * @brief Remove a module from SR internal module data.
 *
 * @param[in] ly_ctx Context to use for parsing SR data.
 * @param[in] new_ctx Context with the module removed.
 * @param[in] mod_set Set of all the removed modules.
 * @param[out] sr_del_mods Deleted modules from @p sr_mods.
 * @param[out] sr_mods SR internal module data.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_change_del_module(const struct ly_ctx *ly_ctx, const struct ly_ctx *new_ctx,
        const struct ly_set *mod_set, struct lyd_node **sr_del_mods, struct lyd_node **sr_mods);

/**
 * @brief Update a module in SR internal module data.
 *
 * @param[in] ly_ctx Context to use for parsing SR data.
 * @param[in] ly_mod Updated module.
 * @param[out] sr_mods SR internal module data.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_change_upd_module(const struct ly_ctx *ly_ctx, const struct lys_module *ly_mod,
        struct lyd_node **sr_mods);

/**
 * @brief Change a feature (enable/disable) of a module in SR internal module data.
 *
 * @param[in] ly_ctx Context to use for parsing SR data.
 * @param[in] old_mod Module with the previous (current) state of features.
 * @param[in] new_mod Module with the features updated.
 * @param[in] feat_name Feature name.
 * @param[in] enable Whether the feature was enabled or disabled.
 * @param[out] sr_mods SR internal module data.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_change_chng_feature(const struct ly_ctx *ly_ctx, const struct lys_module *old_mod,
        const struct lys_module *new_mod, const char *feat_name, int enable, struct lyd_node **sr_mods);

/**
 * @brief Change replay support of a module in SR internal module data.
 *
 * @param[in] conn Connection to use.
 * @param[in] ly_mod Module to update. NULL to update all the modules.
 * @param[in] enable Whether replay should be enabled or disabled.
 * @param[in] mod_set Set of all the changed modules.
 * @param[out] sr_mods SR internal module data.
 * @return err_info, NULL on success.
 */
sr_error_info_t *sr_lydmods_change_chng_replay_support(sr_conn_ctx_t *conn, const struct lys_module *ly_mod,
        int enable, struct ly_set *mod_set, struct lyd_node **sr_mods);

#endif
