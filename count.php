<?php

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
	if(next($arr))
	{
		foreach ($arr as $key => $value) {
			$tmp_arr = $arr;
			array_shift($tmp_arr);
			foreach ($value as $v) {
				$url_arr[$key] = $v;
				echo createUrl($url_arr,$cate)."<br>";
				d($url_arr,$tmp_arr,$cate);
			}
			break;
		}
	}
	elseif(is_array($arr))
	{
		foreach ($arr as $key => $value) {
			foreach ($value as $v) {
				$url_arr[$key] = $v;
				echo createUrl($url_arr,$cate)."<br>";
			}
		}
	}
	else
	{
		return false;
	}
}
?>