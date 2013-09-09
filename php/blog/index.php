<?php
require_once './packages/autoload.php'; 

if($argc<2)
{
    $c = new Colors\Color();

    echo $c("usage:index.php URL")->red.PHP_EOL;
    exit();
}
else
{
    $blog = new Blog\Model\Sina($argv[1]);
    $blog->run();
}

