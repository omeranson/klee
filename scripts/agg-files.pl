#!/usr/bin/perl -s

#use strict;
#use warnings;
use Data::Dumper;

$filename_filter = $ARGV[0];
$file1 = $ARGV[1];
$file2 = $ARGV[2];

# Datastructure:
# file1[function][line number] = cov/uncov (1/0)
# file1_instructions[function] = number of instructions
# file2[function][line number] = cov/uncov (1/0)
# file2_instructions[function] = number of instructions
# Warn if file1_instructions[function] != file2_instructions[function]
# sum[function][line number] = file1[function][line number] OR file2[function][line number]
# Scan file 1.
sub parse_file {
	($inputfilename) = @_;
	open my $fh, $inputfilename or die "Cannot open $inputfilename: $!";
	$filename = "<unknown>";
	my %func_total_lines = ();
	my %func_covered_lines = ();
	while (<$fh>) {
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
			$func_total_lines{$funcname} = 0;
			$inst_idx = 0;
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
				if ($icov + $iuncov > 0) {
					$func_covered_lines{$funcname}{$inst_idx} = $icov;
				}
				$inst_idx += 1;
			}
		}
		if (/^cfn=(.*)/) {
			$called_function = $1;
		}
		$call_result = (/^calls=/);
	}
	return (\%func_total_lines, \%func_covered_lines);
}

($file1_func_total_lines, $file1_covered_lines) = parse_file($file1);
($file2_func_total_lines, $file2_covered_lines) = parse_file($file2);
if (%$file1_func_total_lines != %$file2_func_total_lines) {
	print STDERR "Warning: total lines differ\n";
}
for $funcname (keys %$file1_func_total_lines) {
	if ($$file1_func_total_lines{$funcname} != $$file2_func_total_lines{$funcname}) {
		print STDERR "Warning: total lines differ for $funcname\n";
	}
	$file1_covered_lines_func = %$file1_covered_lines{$funcname};
	$file2_covered_lines_func = %$file2_covered_lines{$funcname};
	@file1_func_lines = keys %$file1_covered_lines_func;
	@file2_func_lines = keys %$file2_covered_lines_func;
	if (@file1_func_lines != @file2_func_lines) {
		print STDERR "Warning: line keys differ for $funcname\n";
	}
	$sum{$funcname} = 0;
	$sum1{$funcname} = 0;
	$sum2{$funcname} = 0;
	for $line_idx (@file1_func_lines) {
		#print "$funcname $line_idx $$file1_covered_lines_func{$line_idx} $$file2_covered_lines_func{$line_idx}\n";
		$line_cov_sum = $$file1_covered_lines_func{$line_idx} + $$file2_covered_lines_func{$line_idx};
		$sum1{$funcname} += $$file1_covered_lines_func{$line_idx};
		$sum2{$funcname} += $$file2_covered_lines_func{$line_idx};
		if ($line_cov_sum > 0) {
			$sum{$funcname} += 1;
		}
	}
}

$tot = 0;
$tot_sum = 0;
$tot_sum1 = 0;
$tot_sum2 = 0;
for $funcname (keys %sum) {
	#print "$funcname $$file1_func_total_lines{$funcname} $sum{$funcname} $sum1{$funcname} $sum2{$funcname}\n";
	$tot += $$file1_func_total_lines{$funcname};
	$tot_sum += $sum{$funcname};
	$tot_sum1 += $sum1{$funcname};
	$tot_sum2 += $sum2{$funcname};
}
print "$tot $tot_sum $tot_sum1 $tot_sum2\n"
