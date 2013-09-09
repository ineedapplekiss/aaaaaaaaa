<?php
namespace Blog\Model;
use Colors\Color;

class Sina {
    public $c;
    public $url;
    public $artList = array();

    public function __construct($url)
    {
        $this->c = new Color();
        $this->url = $url;
    }

    public function run()
    {
        //get list url
        echo call_user_func($this->c,"get blog $this->url start...")->yellow . PHP_EOL;
        $listUrl = $this->getListUrl($this->url);
        
        //get article list
        echo call_user_func($this->c,"download articles ...")->yellow . PHP_EOL;
        $this->getArticle($listUrl);

        while($url = array_shift($this->artList))
        {
            $this->parseArt($url);
        }
    }

    public function getListUrl($url)
    {
        $indexPage= \Blog\Fn\Curl::get($url);
        preg_match("/<span><a  href=\"([^\"]*)\">博文目录<\/a><\/span>/",
            $indexPage,$matches);
        if(!is_array($matches) || !filter_var($matches[1],FILTER_VALIDATE_URL))
        {
            echo call_user_func($this->c,"parse listUrl failed..")->red. PHP_EOL;
            exit(1);
        }
        else
        {
            return $matches[1];
        }
    }

    public function getArticle($url)
    {
        $listPage= \Blog\Fn\Curl::get($url);
        preg_match("/<strong>全部博文<\/strong><em>\((\d+)\)<\/em>/",
            $listPage,$matches);
        if(!is_array($matches) || !filter_var($matches[1],FILTER_VALIDATE_INT))
        {
            echo call_user_func($this->c,"get count article failed..")->red. PHP_EOL;
            exit(1);
        }
        echo "count $matches[1]".PHP_EOL;

        $totalArt = $matches[1];
        $progressBar = new \ProgressBar\Manager(0, $totalArt);
        $max = 30;//最大获取30页
        $artNo = $runNo = 0;
        while($artNo<$totalArt && $runNo<$max)
        {
            $runNo++;
            $curUrl = str_replace("_1.html","_".$runNo.".html",$url);
            if($curUrl != $url)
            {
                $listPage= \Blog\Fn\Curl::get($curUrl);
            }
            if(empty($listPage))
            {
                echo call_user_func($this->c,"$curUrl failed..")->red. PHP_EOL;
                exit(1);
            }
            //echo call_user_func($this->c,"do $curUrl ..")->blue. PHP_EOL;
            preg_match_all("/<a title=\"[^\"]+\" target=\"_blank\" href=\"([^\"]+)\">/",
            $listPage,$matches);

            $this->artList = array_merge($this->artList,$matches[1]);
            $artNo += count($matches[1]);
            $progressBar->update($artNo);
        }
    }

    public function parseArt($url)
    {
        $artCon = \Blog\Fn\Curl::get($url);
        if(!$artCon)
        {
            echo call_user_func($this->c,"get art[$url] con failed..")->red. PHP_EOL;
            return false;
        }
        //title
        preg_match("/class=\"titName SG_txta\">(.*?)<\/h2>/",$artCon,$matches);
        $title = $matches[1];
        echo call_user_func($this->c,"get art[$title] succ..")->dark. PHP_EOL;
    }
}
