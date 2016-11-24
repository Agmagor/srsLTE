/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2015 Software Radio Systems Limited
 *
 * \section LICENSE
 *
 * This file is part of the srsLTE library.
 *
 * srsLTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsLTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

/******************************************************************************
 *  File:         pcfich.h
 *
 *  Description:  Physical control format indicator channel
 *
 *  Reference:    3GPP TS 36.211 version 10.0.0 Release 10 Sec. 6.7
 *****************************************************************************/

#ifndef PCFICH_
#define PCFICH_

#include "srslte/config.h"
#include "srslte/common/phy_common.h"
#include "srslte/mimo/precoding.h"
#include "srslte/mimo/layermap.h"
#include "srslte/modem/mod.h"
#include "srslte/modem/demod_soft.h"
#include "srslte/scrambling/scrambling.h"
#include "srslte/phch/regs.h"

#define PCFICH_CFI_LEN  32
#define PCFICH_RE       PCFICH_CFI_LEN/2

/* PCFICH object */
typedef struct SRSLTE_API {
  srslte_cell_t cell;
  int nof_symbols;

  /* handler to REGs resource mapper */
  srslte_regs_t *regs;

  /* buffers */
  cf_t ce[SRSLTE_MAX_PORTS][PCFICH_RE];
  cf_t symbols[SRSLTE_MAX_PORTS][PCFICH_RE];
  cf_t x[SRSLTE_MAX_PORTS][PCFICH_RE];
  cf_t d[PCFICH_RE];

  // cfi table in floats
  float cfi_table_float[3][PCFICH_CFI_LEN];

  /* bit message */
  uint8_t data[PCFICH_CFI_LEN];

  /* received soft bits */
  float data_f[PCFICH_CFI_LEN];

  /* tx & rx objects */
  srslte_modem_table_t mod;
  srslte_sequence_t seq[SRSLTE_NSUBFRAMES_X_FRAME];

} srslte_pcfich_t;

SRSLTE_API int srslte_pcfich_init(srslte_pcfich_t *q,
                           srslte_regs_t *regs,
                           srslte_cell_t cell);

SRSLTE_API void srslte_pcfich_free(srslte_pcfich_t *q);

SRSLTE_API int srslte_pcfich_decode(srslte_pcfich_t *q,
                             cf_t *sf_symbols,
                             cf_t *ce[SRSLTE_MAX_PORTS],
                             float noise_estimate,
                             uint32_t subframe,
                             uint32_t *cfi,
                             float *corr_result);

SRSLTE_API int srslte_pcfich_encode(srslte_pcfich_t *q,
                             uint32_t cfi,
                             cf_t *sf_symbols[SRSLTE_MAX_PORTS],
                             uint32_t subframe);

#endif
