<?php
set_time_limit(0);
ini_set("memory_limit","1000M");
header("Content-type:text/html;charset=utf-8");


m();

/**
* test
*/
class test
{
	public $data;
	public function __construct($num,$v)
	{
		$this->data = new SplFixedArray(6);
		$this->data[5][$num] = $v;
	}
	public function show()
	{
		var_dump($this->data);
	}


}

$a = new test('aa',33);

$a->show();

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
