/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */
#include "power_management.h"

#include <stdio.h>
#include <string.h>

#include "services_lib_api.h"
#include "services_lib_bare_metal.h"
#include "power_profile.h"

// SE handle
extern uint32_t se_services_s_handle;

void print_runprofile(const run_profile_t *runprof) {
    printf("memory_blocks   %08X\n", runprof->memory_blocks);
    printf("power_domains   %08X\n", runprof->power_domains);
    printf("ip_clock_gating %08X\n", runprof->ip_clock_gating);
    printf("phy_pwr_gating  %08X\n", runprof->phy_pwr_gating);
    printf("vdd_ioflex_3V3  %08X\n", runprof->vdd_ioflex_3V3);
    printf("run_clk_src     %08X\n", runprof->run_clk_src);
    printf("aon_clk_src     %08X\n", runprof->aon_clk_src);
    printf("scaled_clk_freq %08X\n", runprof->scaled_clk_freq);
    printf("dcdc_mode       %08X\n", runprof->dcdc_mode);
    printf("dcdc_voltage    %u\n", runprof->dcdc_voltage);
}

static bool set_power_profiles(void) {

    uint32_t service_error_code;
    uint32_t err = 0;

    // Get SERAM revision string
    uint8_t revision_data[80];
    err = SERVICES_get_se_revision(se_services_s_handle, revision_data, &service_error_code);
    if (err || service_error_code) {
        return false;
    }

    // Parse SERAM version
    const char *ver_str_ptr = strstr(revision_data, " v");
    int ver_maj = 0;
    int ver_min = 0;
    int ver_patch = 0;
    int result = sscanf(ver_str_ptr, " v%d.%d.%d", &ver_maj, &ver_min, &ver_patch);
    if (result != 3) {
        return false;
    }

    // Build combined version for easy comparison
    const uint32_t ver_comp = (ver_maj << 16) | (ver_min << 8) | ver_patch;

    // run profile enumerations changed after 107
    run_profile_t *default_runprof = NULL;
    off_profile_t *default_offprof = NULL;
    const uint32_t ver1_107_0 = (1 << 16) | (107 << 8);
    if (ver_comp > ver1_107_0) {
        default_runprof = get_runprof_109();
        default_offprof = get_offprof_109();
    } else {
        default_runprof = get_runprof_107();
        default_offprof = get_offprof_107();
    }

    err = SERVICES_set_run_cfg(se_services_s_handle, default_runprof, &service_error_code);

    if (err == 0 && service_error_code == 0) {
        err = SERVICES_set_off_cfg(se_services_s_handle, default_offprof, &service_error_code);
    }

    return err == 0 && service_error_code == 0;
}

bool init_power_management(void) {
    return set_power_profiles();
}
