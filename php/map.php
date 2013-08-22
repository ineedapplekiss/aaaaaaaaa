<?php
error_reporting(0);
$wd = $argv[1] ? $argv[1] : $_GET['wd'];

//tian an door
$lng = 116.404015;//东经
$lat = 39.912733;//北纬
$x = 12958176.7;//平面坐标X
$y = 4825596.3;//平面坐标Y

//rate
$xRate = '0.000008983';//每一个平面坐标X轴偏移1时，la的偏移量
$yRate = '0.000006914';

$url = "http://api.map.baidu.com/?qt=s&c=131&wd=$wd&rn=10&ie=utf-8&oue=1&res=api";
$res = json_decode(getUrl($url),true);
foreach((array)$res['content'] as $val)
{
    if(empty($val['ext']['detail_info']['point'])) {
        echo "=======================><br>";
        var_dump($val);
        echo "<br>";
        continue;
    }

    //$vLng = $lng+($val['ext']['detail_info']['point']['x']-$x)*$xRate;
    $vLng = bcadd(
                $lng,
                bcmul(
                    bcsub($val['ext']['detail_info']['point']['x'],$x,2),
                    $xRate,
                    30
                ),
                6
            );
    //$vLat = $lat+($val['ext']['detail_info']['point']['y']-$y)*$yRate;
    $vLat = bcadd(
                $lat,
                bcmul(
                    bcsub($val['ext']['detail_info']['point']['y'],$y,2),
                    $yRate,
                    30
                    ),
                6
            );

    
    printf("========================><br>
    %s<br>
    addr:%s<br>
    tel:%s<br>
    xy:%s<br>
    ll:%s<br>",
    $val['ext']['detail_info']['name'],
    $val['ext']['detail_info']['poi_address'],
    $val['ext']['detail_info']['phone'],
    $val['ext']['detail_info']['point']['x'].','.$val['ext']['detail_info']['point']['y'],
    $vLng.','.$vLat
    );
}

function getUrl($url, $timeout = 3, $userpwd = '', $host_ip = null) {
    $ch = curl_init();
	if (!is_null($host_ip))
	{
		$urldata = parse_url($url);
		if (!empty($urldata['query']))
		{
			$urldata['path'] .= "?" . $urldata['query'];
		}
		$headers = array("Host: " . $urldata['host']);
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
		$url = $urldata['scheme'] . "://" . $host_ip . $urldata['path'];
	}

    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
    if ($userpwd != '') {
        curl_setopt($ch, CURLOPT_USERPWD, $userpwd);
    }
    $ret = curl_exec($ch);
    curl_close($ch);
    return $ret;
}


