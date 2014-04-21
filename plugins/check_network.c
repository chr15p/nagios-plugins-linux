/*
 * License: GPLv3+
 * Copyright (c) 2014 Davide Madrisan <davide.madrisan@gmail.com>
 *
 * A Nagios plugin that displays some network interfaces.statistics.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <linux/if_link.h>

#include "common.h"
#include "messages.h"
#include "netinfo.h"
#include "progname.h"
#include "progversion.h"
#include "thresholds.h"
#include "xalloc.h"

static const char *program_copyright =
  "Copyright (C) 2014 Davide Madrisan <" PACKAGE_BUGREPORT ">\n";

static struct option const longopts[] = {
  {(char *) "critical", required_argument, NULL, 'c'},
  {(char *) "warning", required_argument, NULL, 'w'},
  {(char *) "help", no_argument, NULL, GETOPT_HELP_CHAR},
  {(char *) "version", no_argument, NULL, GETOPT_VERSION_CHAR},
  {NULL, 0, NULL, 0}
};

static _Noreturn void
usage (FILE * out)
{
  fprintf (out, "%s (" PACKAGE_NAME ") v%s\n", program_name, program_version);
  fputs ("This plugin displays some network interfaces.statistics.\n", out);
  fputs (program_copyright, out);
  fputs (USAGE_HEADER, out);
  fprintf (out, "  %s -w COUNTER|PERC -c COUNTER|PERC\n", program_name);
  fputs (USAGE_OPTIONS, out);
  fputs ("  -w, --warning COUNTER   warning threshold\n", out);
  fputs ("  -c, --critical COUNTER   critical threshold\n", out);
  fputs (USAGE_HELP, out);
  fputs (USAGE_VERSION, out);
  fputs (USAGE_EXAMPLES, out);
  fprintf (out, "  %s\n", program_name);

  exit (out == stderr ? STATE_UNKNOWN : STATE_OK);
}

static _Noreturn void
print_version (void)
{
  printf ("%s (" PACKAGE_NAME ") v%s\n", program_name, program_version);
  fputs (program_copyright, stdout);
  fputs (GPLv3_DISCLAIMER, stdout);

  exit (STATE_OK);
}

int
main (int argc, char **argv)
{
  int c;
  //char *critical = NULL, *warning = NULL;
  //thresholds *my_threshold = NULL;
  nagstatus status = STATE_OK;
  //unsigned int sleep_time = 1;

  set_program_name (argv[0]);

  while ((c = getopt_long (argc, argv,
			   /*"c:w:"*/ GETOPT_HELP_VERSION_STRING,
			   longopts, NULL)) != -1)
    {
      switch (c)
	{
	default:
	  usage (stderr);
	//case 'c':
	//  critical = optarg;
	//  break;
	//case 'w':
	//  warning = optarg;
	//  break;

	case_GETOPT_HELP_CHAR
	case_GETOPT_VERSION_CHAR

	}
    }

  //status = set_thresholds (&my_threshold, warning, critical);
  //if (status == NP_RANGE_UNPARSEABLE)
  //  usage (stderr);

  //status = get_status (..., my_threshold);
  //free (my_threshold);

  printf ("%s %s | ", program_name_short, state_text (status));

  iflist_t *ifl, *iflhead = netinfo ();

  /* lo-rxkB/s=0.00;;;; lo-txkB/s=0.00;;;; lo-rxerr/s=0.00;;;;
   *  lo-txerr/s=0.00;;;; lo-rxdrop/s=0.00;;;; lo-txdrop/s=0.00;;;;
   * eth1-rxkB/s=231.39;;;; eth1-txkB/s=196.18;;;; eth1-rxerr/s=0.00;;;; 
   *  eth1-txerr/s=0.00;;;; eth1-rxdrop/s=0.00;;;; eth1-txdrop/s=0.00;;;;
   */
  for (ifl = iflhead; ifl != NULL; ifl = ifl->next)
    printf ("%s_txpck=%u %s_rxpck=%u %s_txbyte=%u %s_rxbyte=%u "
	    "%s_txerr=%u %s_rxerr=%u %s_txdrop=%u %s_rxdrop=%u "
	    "%s_mcast=%u %s_coll=%u ",
	    ifl->ifname, ifl->tx_packets, ifl->ifname, ifl->rx_packets,
	    ifl->ifname, ifl->tx_bytes,   ifl->ifname, ifl->rx_bytes,
	    ifl->ifname, ifl->tx_errors,  ifl->ifname, ifl->rx_errors,
            ifl->ifname, ifl->tx_dropped, ifl->ifname, ifl->rx_dropped,
            ifl->ifname, ifl->multicast,  ifl->ifname, ifl->collisions
    );
  putchar ('\n');
  freeiflist (iflhead);
}
