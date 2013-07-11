/*****************************************************************************
 *
 * SRETENTION.C - State retention routines for Icinga
 *
 * Copyright (c) 1999-2008 Ethan Galstad (egalstad@nagios.org)
 * Copyright (c) 2009-2013 Nagios Core Development Team and Community Contributors
 * Copyright (c) 2009-2013 Icinga Development Team (http://www.icinga.org)
 *
 * License:
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *****************************************************************************/

/*********** COMMON HEADER FILES ***********/

#include "../include/config.h"
#include "../include/common.h"
#include "../include/objects.h"
#include "../include/statusdata.h"
#include "../include/icinga.h"
#include "../include/sretention.h"
#include "../include/broker.h"

extern int            retain_state_information;



/**** IMPLEMENTATION SPECIFIC HEADER FILES ****/
#ifdef USE_XRDDEFAULT
#include "../xdata/xrddefault.h"		/* default routines */
#endif






/******************************************************************/
/************* TOP-LEVEL STATE INFORMATION FUNCTIONS **************/
/******************************************************************/


/* initializes retention data at program start */
int initialize_retention_data(char *config_file) {
	int result = OK;

	/**** IMPLEMENTATION-SPECIFIC CALLS ****/
#ifdef USE_XRDDEFAULT
	result = xrddefault_initialize_retention_data(config_file);
#endif

	return result;
}



/* cleans up retention data before program termination */
int cleanup_retention_data(char *config_file) {
	int result = OK;

	/**** IMPLEMENTATION-SPECIFIC CALLS ****/
#ifdef USE_XRDDEFAULT
	result = xrddefault_cleanup_retention_data(config_file);
#endif

	return result;
}



/* save all host and service state information */
int save_state_information(int autosave) {
	int result = OK;

	if (retain_state_information == FALSE)
		return OK;

#ifdef USE_EVENT_BROKER
	/* send data to event broker */
	broker_retention_data(NEBTYPE_RETENTIONDATA_STARTSAVE, NEBFLAG_NONE, NEBATTR_NONE, NULL);
#endif

	/********* IMPLEMENTATION-SPECIFIC OUTPUT FUNCTION ********/
#ifdef USE_XRDDEFAULT
	result = xrddefault_save_state_information();
#endif

#ifdef USE_EVENT_BROKER
	/* send data to event broker */
	broker_retention_data(NEBTYPE_RETENTIONDATA_ENDSAVE, NEBFLAG_NONE, NEBATTR_NONE, NULL);
#endif

	if (result == ERROR)
		return ERROR;

	if (autosave == TRUE)
		logit(NSLOG_PROCESS_INFO, FALSE, "Auto-save of retention data completed successfully.\n");

	return OK;
}




/* reads in initial host and state information */
int read_initial_state_information(void) {
	int result = OK;

	if (retain_state_information == FALSE)
		return OK;

#ifdef USE_EVENT_BROKER
	/* send data to event broker */
	broker_retention_data(NEBTYPE_RETENTIONDATA_STARTLOAD, NEBFLAG_NONE, NEBATTR_NONE, NULL);
#endif

	/********* IMPLEMENTATION-SPECIFIC INPUT FUNCTION ********/
#ifdef USE_XRDDEFAULT
	result = xrddefault_read_state_information();
#endif

#ifdef USE_EVENT_BROKER
	/* send data to event broker */
	broker_retention_data(NEBTYPE_RETENTIONDATA_ENDLOAD, NEBFLAG_NONE, NEBATTR_NONE, NULL);
#endif

	if (result == ERROR)
		return ERROR;

	return OK;
}

/* syncs host and state information from sync file */
/* Should this go within read_state_information()? */
int sync_state_information(void) {
	int result = OK;

	if (retain_state_information == FALSE)
		return OK;

	/********* IMPLEMENTATION-SPECIFIC INPUT FUNCTION ********/
#ifdef USE_XRDDEFAULT
	result = xrddefault_sync_state_information();
#endif

	if (result == ERROR)
		return ERROR;

	return OK;
}

