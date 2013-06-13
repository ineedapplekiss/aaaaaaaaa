<?php
//------------------------------------------------------------
//求总数用的数组
//------------------------------------------------------------
$arr = array(
	array(37),
	array(2,11),
	array(2,5,3,4,2),
	array(2,11,5,4),
	array(11,5),
	array(2,16),
	array(2,16,2,5,4),
	array(14,6),
	array(11,5),
	array(33),
	array(9,2,4),
	array(27,2,4,2),
	array(17,3,6,3),
	array(7),
	array(21,3,4,3,4,2,2,2),
	array(14,3,4,4,2,5,2),
	array(15,6,4,2),
	array(3,2),
	array(2,6),
	array(21,6,4,5,6,4,5,2),
	array(3,8),
	array(3,1,2),
	array(3,4,3,1),
	array(3,6,4,6,2,2,3),
	array(14),
	array(56),
	array(43,2,7,7,6,5,10,2),
	array(34,6),
	array(18,7),
	array(11,3),
	array(3,9),
	array(3,6,2,4,2,4),
	array(3,5,5,2),
	array(3,2,1),
	array(40),
	array(23,4,2,2),
	array(35,2,3,2,2),
	array(27,3,2),
	array(5,2,1),
	array(21,3,2),
	array(34,2),
	array(19,6,2),
	array(23),
	array(6,4,4,2),
	array(5,2,2,2,4),
	array(3,3),
	array(8,4,5,4,2,2),
	array(4,4),
	array(1,1),
	array(5,9),
);

//------------------------------------------------------------
//模拟数据库数据，批量生成url
//------------------------------------------------------------
$arr = array(
	'chuwei' => array(
		'brand' => array('diwei','dc2','toto'),
		'a' 	=> array(0,1,2,3),
		'b'		=> array(0,1),
		'c'		=> array(0,1),
	)
);
//------------------------------------------------------------
//遍历数组
//------------------------------------------------------------
foreach ($arr as $a_k => $a_v) {
	//处理单个分类的数据
	d(array() , $a_v , $a_k);
}

/**
 * 生成url function
 *
 * @return void
 * @author zhiliang
 **/
function createUrl($arr , $cate='cate')
{
	$url = 'http://www.jiaju.com/c-'.$cate;
	$brand = is_array($arr['brand']) ? array_shift($arr['brand']) : $arr['brand'];
	$url .= isset($arr['brand']) ? '/'.$brand.'/' : "/all/";
	unset($arr['brand']);
	ksort($arr);
	if($arr)
	{
		foreach ($arr as $key => $value) {
			$value = is_array($value) ? array_shift($value) : $value;
			$arr[$key] = $key.$value;
		}
		$url .= implode("-",$arr);
	}
	return $url;
}

/**
 * 批处理一个分类下的所有数据 function
 *
 * @return next 
 * @author zhiliang
 **/
function d($url_arr , $arr , $cate)
{
	if(is_array($arr))
	{
		foreach ($arr as $key => $value) {
			$url_arr[$key] = array_shift($arr[$key]);
			if(empty($arr[$key]))unset($arr[$key]);
			if(next($arr))
			{
				$tmp_arr = $arr;
				array_shift($tmp_arr);
				d($url_arr,$tmp_arr,$cate);
			}
			break;
		}
		
	}
	return false;
}
?>