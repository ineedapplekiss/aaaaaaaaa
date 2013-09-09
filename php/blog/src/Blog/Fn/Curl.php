<?php
namespace Blog\Fn;

class Curl {
    static public function get($url, $timeout = 1)
    {
        $i = 0;
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
        while(empty($ret) && $i<3)
        {            
            $ret = curl_exec($ch);
            $i++;
        }
        curl_close($ch);
        return $ret;
    }
}
