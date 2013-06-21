<?php

set_time_limit(0);
$runtime = 0;

m();
$start_timestamp = microtime(true);
$end = 120000;

$start = 1;
while ($start < $end) {
	$runtime++;
	$from_num  = $start;
	$start++;
	run($from_num , $start , $end);
}
$end_timestamp = microtime(true);

m();
mp();
var_dump($start_timestamp,$end_timestamp);
echo $runtime;

/**
 * undocumented function
 *
 * @return void
 * @author zhiliang
 **/
function run($from_num , $start=1 , $end = 1200)
{
	global $runtime;
	while ($start <= $end) {
		//echo $from_num.'--'.$start."\n";
		$runtime++;
		$start++;
	}
}



function m()
{
	    $m = memory_get_usage();
		    echo floor($m/1024)."k----[".floor($m/1024/1024)." M] \n";
}

function mp()
{
	    $m = memory_get_peak_usage();
		    echo 'peak:'.floor($m/1024)."k----[".floor($m/1024/1024)." M] \n";
}