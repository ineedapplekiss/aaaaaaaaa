<?php

set_time_limit(0);
$runtime = 0;

//--------------------------------------------------------
// 开始时间，开始内存
//--------------------------------------------------------
m();
$start_timestamp = microtime(true);


//--------------------------------------------------------
// 模拟数组
//--------------------------------------------------------
$arr = array(
	'cate1' => array(//分类下数据
		array(11,12,13,14,15),//商铺下商品数据
		array(21,22,23,24),
		array(31,32,33,34)
	),
	'cate2' => array(
		array(11,12,13,14,15),
		array(21,22,23,24),
		array(31,32,33,34)
	),
);
foreach ($arr as $k => $v) {
	while (list($s_pos,$s_val) = each($v)) {
		while (list($g_pos,$g_val) = each($s_val)) {
			run($s_pos,$g_pos,$v);
		}
	}
}



//--------------------------------------------------------
// 内存和运行时间
//--------------------------------------------------------
$end_timestamp = microtime(true);
m();
mp();
var_dump($start_timestamp,$end_timestamp);
echo $runtime;

/**
 * 与给定位置之后的所有id生成url
 *
 * @return void
 * @author zhiliang
 **/
function run($shop_pos,$goods_pos,$cate_data)
{
	$a_id = $cate_data[$shop_pos][$goods_pos];

	while (list($s_pos,$s_val) = each($cate_data)) {
		if($s_pos <= $shop_pos)continue;
		while (list($g_pos,$g_val) = each($s_val)) {
			echo url($a_id,$g_val);
		}
	}
}

function url($a_id,$b_id)
{
	global $runtime;
	$runtime++;
	return $a_id.'--'.$b_id."\n";
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