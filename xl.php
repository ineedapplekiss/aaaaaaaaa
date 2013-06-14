<?php
$arr = array(
		'brand' => array('diwei','dc2','toto', 'all'),
		'a' 	=> array(0,1,2,3),
		'b'		=> array(0,1),
		'c'		=> array(0,1),
);
var_dump( geturl( '', array_keys($arr) ) );

function geturl($prefix, $keys)
{
	global $arr;
	$res = array();
	$key = array_shift($keys);
	//var_dump(substr($prefix, -1));
	if(substr($prefix, -1) == '-')
	{
		$res[] = substr($prefix, 0, strlen($prefix)-1).'/';
	}
	else
	{
		$res[] = $prefix;
	}
	// the last level
	if(empty($keys))
	{

		foreach($arr[$key] as $v)
		{
			$res[] = join_url($prefix, $key, $v, true);
		}
	}
	else
	{
		foreach($arr[$key] as $v)
		{
			$prefix_new = join_url($prefix, $key, $v);
			$res = array_merge($res, geturl($prefix_new, $keys));
		}
	}
	return $res;
}

function join_url($prefix, $key, $v, $last = false)
{
	if($key == 'brand')
	{
		return $prefix.'/'.$v.'/';
	}
	else
	{
		$subfix = $last ? '/' : '-';
		return $prefix.$key.$v.$subfix;
	}
}
