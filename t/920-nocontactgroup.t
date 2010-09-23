#!/usr/bin/perl
# 
# Check that no service gives the correct message

use warnings;
use strict;
use Test::More qw(no_plan);
use FindBin qw($Bin);

chdir $Bin or die "Cannot chdir";

my $topdir = "$Bin/..";
my $nagios = "$topdir/base/icinga";
my $etc = "$Bin/etc";
my $precache = "$Bin/var/objects.precache";


my $output = `$nagios -v "$etc/icinga-no-contactgroup.cfg"`;
like( $output, "/Error: Could not find any contactgroup matching 'nonexistantone'/", "Correct error for no services" );
isnt($?, 0, "And get return code error" );