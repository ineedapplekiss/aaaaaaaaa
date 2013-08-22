<?php
$data = array(
        0 => array(
            "name" => "天安门",
            "lng" => 116.404015,
            "lat" => 39.912733,
            "x" => 12958176.7,
            "y" => 4825596.3,
            ),
        1 => array(
            "name" => "首东国际",
            "lng" => 116.453529,
            "lat" => 39.899006,
            "x" => 12963688.6,
            "y" => 4823612.8,
            ),
        2 => array(
            "name" => "山城辣妹子",
            "lng" => 116.386021,
            "lat" => 39.985863,
            "x" => 12956173.59,
            "y" => 4836173.5,
            ),
        3 => array(
            "name" => "顺景温泉",
            "lng" => 116.47051,
            "lat" => 39.979008,
            "x" => 12965578.9, 
            "y" => 4835181.6,
            ),
        4 => array(
            "name" => "全聚德",
            "lng" => 116.456331,
            "lat" => 39.914746,
            "x" => 12964000.55,
            "y" => 4825887.91,
            ),
        5 => array(
            "name" => "巫山烤全鱼",
            "lng" => 116.309382,
            "lat" => 40.048442,
            "x" => 12947642.08,
            "y" => 4845233.54,
            ),

        );
foreach($data as $k => $v)
{
    $subData = $data;
    while($sub = array_pop($subData))
    {
        if($v == $sub)break;
        getRate($v,$sub);
    }
    echo "=========><br>";
}

function getRate($a,$b)
{
    $xRate = bcdiv(
                abs(bcsub($b['lng'],$a['lng'],6)),
                abs(bcsub($b['x'],$a['x'],2)),
                30
             );
    $yRate = bcdiv(
                abs(bcsub($b['lat'],$a['lat'],6)),
                abs(bcsub($b['y'],$a['y'],2)),
                30
             );
    printf("xR:%s<br>yR:%s<br>===========><br>",$xRate,$yRate); 
    return 0;
}


