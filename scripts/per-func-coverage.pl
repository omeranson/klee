#!/usr/bin/perl -s

#use warnings;

$filename_filter = "";
if ($f) {
	$filename_filter = $f;
}

# Scan the run.istats output from klee. OUtput for each function the coverage.
# ^fl= means filename, ^fn=means start of function
$filename = "<unknown>";
while (<>) {
	if (/^fl=(.*)/) {
		$filename = $1;
		if ($filename =~ /^\s*$/) {
			$filename = "<unknown>";
		}
	}
	if ($filename_filter) {
		if (!($filename =~ /$filename_filter/)) {
			next;
		}
	}
	if (/^fn=(.*)/) {
		$funcname = $1;
		$func_files{$funcname} = $filename;
		$func_total_lines{$funcname} = 0;
		$func_covered_lines{$funcname} = 0;
		$func_forks{$funcname} = 0;
		$func_qtime{$funcname} = 0;
		$func_children_forks{$funcname} = 0;
		$func_children_qtime{$funcname} = 0;
	}
	if (/^(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s*$/) {
		$assembly_line = $1;
		$source_line = $2;
		$icov = $3;
		$forks = $4;
		$ireal = $5;
		$itime = $6;
		$instructions = $7;
		$ucdist = $8;
		$rtime = $9;
		$states = $10;
		$iuncov = $11;
		$q = $12;
		$qiv = $13;
		$qv = $14;
		$qtime = $15;

		if (!$call_result) {
			$func_total_lines{$funcname} += $icov + $iuncov;
			$func_covered_lines{$funcname} += $icov;
			$func_forks{$funcname} += $forks;
			$func_qtime{$funcname} += $qtime;
		}
		$func_children_forks{$funcname} += $forks;
		$func_children_qtime{$funcname} += $qtime;
	}
	if (/^cfn=(.*)/) {
		$called_function = $1;
	}
	if (/^calls=(\d+)\s+(\d+)\s+(\d+)\s*$/) {
		$call_count = $1;
		if ($called_function) {
			$func_calls{$called_function} += $call_count;
		}
		$called_function = ""
	}
	$call_result = (/^calls=/);
}

$total_forks = 0;
$total_qtime = 0;
$total_inst = 0;
$total_icov = 0;
for $funcname (keys %func_files) {
	#print "Processing $funcname\n";
	$ratio = $func_total_lines{$funcname}>0 ? $func_covered_lines{$funcname}/$func_total_lines{$funcname} : 0;
	$func_call = $func_calls{$funcname};
	if (!$func_call) {
		$func_call = 0;
	}
	print "$func_files{$funcname} $funcname $func_forks{$funcname} $func_children_forks{$funcname} $func_qtime{$funcname} $func_children_qtime{$funcname} $func_call $func_covered_lines{$funcname} $func_total_lines{$funcname} $ratio\n";
	$total_forks += $func_forks{$funcname};
	$total_qtime += $func_qtime{$funcname};
	$total_icov += $func_covered_lines{$funcname};
	$total_inst += $func_total_lines{$funcname};
}

print "Total: Forks: $total_forks QTime: $total_qtime Insts: $total_inst ICov: $total_icov\n";
