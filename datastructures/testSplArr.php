<?php
set_time_limit(0);
ini_set("memory_limit","1000M");
header("Content-type:text/html;charset=utf-8");


m();

$elements = 20;
for($size = 1000; $size < 5000000; $size *= 2) {
    echo PHP_EOL . "Testing size: $size" . PHP_EOL;
    for($s = microtime(true), $i = 0 , $container=array(); $i < $size; $i++) {
            $container[$i] = NULL;
    }
    echo "Array(): " . (microtime(true) - $s) . PHP_EOL;
    m();

    for($s = microtime(true), $i = 0,$container=new SplFixedArray($size); $i < $size; $i++) {
            $container[$i] = NULL;
    }
    echo "SplArray(): " . (microtime(true) - $s) . PHP_EOL;
    m();
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

?>
