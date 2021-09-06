#!/usr/bin/perl
use Net::Telnet;
use Switch;

print "*********************************\n";
print "* jtagprog for use with OpenOCD *\n";
print "*   unlock/flash/lock-utility   *\n";
print "*********************************\n";

$lock = 0;
$flash = 0;
$unlock = 0;
$help = 0;
$run = 0;
$erase = 0;

if($#ARGV == -1)
{
	# no arguments given
	print "INFO: using defaults - unlock, flash with file 'main.bin', run program\n";
	$unlock = 1;	# default --> do unlock
	$flash = 1;	# default --> do flash
	$run = 1;	# default --> run program
}
elsif($#ARGV > 2)
{
	# more than 3 arguments given
	die( "ERROR: execution aborted, more than 3 arguments given!\n\n")
} 
else
{
	# arguments given
	switch ($ARGV[0])
	{
		case "-u"	{ $unlock = 1 }
		case "-f"	{ $flash = 1 }
		case "-l"	{ $lock = 1 }
		case "-r"	{ $run = 1 }
		case "-e"	{ $erase = 1 }
		case "-h"	{ $help = 1 }
		else
		{ 
			print "ERROR: execution aborted, argument 1 not valid!\n\n";
			$help = 1;
		}
	}
	switch ($ARGV[1])
	{
		case "-u"	{ $unlock = 1 }
		case "-f"	{ $flash = 1 }
		case "-l"	{ $lock = 1 }
		case "-r"	{ $run = 1 }
		case "-e"	{ $erase = 1 }
		else
		{ 
			if($#ARGV >= 1)
			{ 			
				print "ERROR: execution aborted, argument 2 not valid!\n\n";
				$help = 1;
			}
		}
	}
	switch ($ARGV[2])
	{
		case "-u"	{ $unlock = 1 }
		case "-f"	{ $flash = 1 }
		case "-l"	{ $lock = 1 }
		case "-r"	{ $run = 1 }
		case "-e"	{ $erase = 1 }
		else
		{ 
			if($#ARGV >= 2)
			{ 			
				print "ERROR: execution aborted, argument 3 not valid!\n\n";
				$help = 1;
			}
		}
	}
}

if ($erase != 0)
{	
	# erase option given, ignore other options
	$unlock = 0;
	$flash = 0;
	$lock = 0;
	$run = 0;
}

if ($help == 1)
{
	print "program usage:\n";
	print "    ./jtagprog.pl [-options ...]\n";
	print "where options include:\n";
	print "    -u        unlock device\n";
	print "    -e        erase device (all other options given will be ignored)\n";
	print "    -f        flash device with file 'main.bin' (including prior erase)\n";
	print "    -l        lock device\n";
	print "    -r        run program (no effect when -l option is given)\n";
	print "    -h        print out this message\n";
	print "examples:\n";
	print "    ./jtagprog.pl -u -f -l\n";
	print "    ./jtagprog.pl -l\n";
	print "    ./jtagprog.pl -u\n";
	print "    ./jtagprog.pl -u -f -r\n";
	print "info:\n";
	print "    - when running program OpenOCD must already be started\n";
	print "    - when -l option is given adjacent power down cycle is mandatory\n";
	print "    - for sole erase of unlocked device use -e option, -u has no effect\n\n";
	exit 0;
}

$filename = './main.bin';
if (($flash == 1) && !(-e $filename))
{
	# flash requested, but file does not exist 
	die( "ERROR: execution aborted, file 'main.bin' does not exist!\n\n")
} 

$ip = "127.0.0.1"; 
$port = 4444;

$telnet = new Net::Telnet (
    Port   => $port,
    Timeout=>10,
    Errmode=>'die',
    Prompt =>'/>/');

$telnet->open($ip);

print $telnet->cmd('reset halt');
print $telnet->cmd('flash probe 0');
if ($unlock == 1)
{
	print "INFO: unlock device\n";
	print $telnet->cmd('stm32f1x unlock 0');
	print $telnet->cmd('reset halt');
}
if ($flash == 1)
{
	print "INFO: flash device with file 'main.bin'\n";
	print $telnet->cmd('stm32f1x mass_erase 0');
	print $telnet->cmd('flash write_bank 0 main.bin 0');
}
if ($erase == 1)
{
	print "INFO: erase device\n";
	print $telnet->cmd('stm32f1x mass_erase 0');
}
if ($lock == 1)
{
	print "INFO: lock device\n";
	print $telnet->cmd('stm32f1x lock 0');
}
print $telnet->cmd('reset halt');
if ($run == 1)
{
	print "INFO: run program\n";
	print $telnet->cmd('reset run');
}
print $telnet->cmd('exit');
print "\n";

