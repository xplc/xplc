#! /usr/bin/perl -w

use strict;

while(<>) {
	s/{?([0-9A-Fa-f]{8})-([0-9A-Fa-f]{4})-([0-9A-Fa-f]{4})-([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})-([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})}?/{0x$1, 0x$2, 0x$3, {0x$4, 0x$5, 0x$6, 0x$7, 0x$8, 0x$9, 0x$10, 0x$11}}/;
} continue {
	print;
}

