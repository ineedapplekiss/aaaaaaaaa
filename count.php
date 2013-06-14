<?php
/**
 * 要求：组合$arr数组内的元素值，生成url，将各种组合输出，正确值为179种
 *
 * 说明：$arr数组本为商品列表页的属性，参见http://www.jiaju.com/c-shuicaobxg/ ；具体链接生成规则也参考列表页
 *
 */
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
	$brand = isset($arr['brand']) && is_array($arr['brand']) ? array_shift($arr['brand']) : isset($arr['brand']) ? $arr['brand'] : 'all';
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
	$arr_count = count($arr);
	$l = 1;
	//组合各种url_arr
	foreach ($arr as $key => $value) {
		foreach ($value as $v) {
			$current_url_arr = array();
			$current_url_arr[$key] = $v;
			$url = array_merge($current_url_arr,$url_arr);
			echo createUrl($url,$cate)."<br>";
			//判断是否有剩余数据进行递归
			if($l<$arr_count)
			{
				$surplus_arr = array_slice($arr,$l);
				d($url,$surplus_arr,$cate);
			}
		}
		$l++;
	}
	return false;
}
?>