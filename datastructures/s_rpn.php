<?php
require 'stack.php';
/**
 * 逆波兰算法
 * reverse polish notation
 */
class rpn
{
	private $me,$re;

	private $config = array(
		'(' => 30,
		')' => 30,
		'*' => 20,
		'/' => 20,
		'+' => 10,
		'-' => 10,
	);//允许的运算符以及权重

	public function __construct($expression)
	{
		$this->me = new SplQueue();
		$eLen = strlen($expression);
		for ($i=0; $i < $eLen; $i++) {
			if(!is_numeric($expression[$i]) && !isset($this->config[$expression[$i]]))return false;
			if(is_numeric($expression[$i]))
			{
				$num = $expression[$i];
				while(is_numeric($expression[$i+1]))
				{
					$i++;
					$num = $num.$expression[$i];
				}
				$this->me->enqueue($num);
			}
			else
			{
				$this->me->enqueue($expression[$i]);
			}
		}
		$this->mToR();
	}

	/**
	 * 中缀转后缀表达式
	 *
	 * @return void
	 * @author zhiliang
	 **/
	private function mToR()
	{
		$rStack = new stack($this->me->count());
		$this->re = new SplQueue();
		foreach ($this->me as $value) {
			if(is_numeric($value))//如果是数字，直接进队列
			{
				$this->re->enqueue($value);
			}
			elseif(isset($this->config[$value]))
			{
				if($value == ')')
				{
					while ($d = $rStack->pop()) {
						if($d != '(')
							$this->re->enqueue($d);
						else
							break;
					}
				}
				else
				{
					$top = $rStack->pop();
					var_dump($value,$top,"=========>\n");
					if($top && ($this->config[$value] <= $this->config[$top]))
					{
						$this->re->enqueue($top);
						$rStack->push($value);
					}
					else
					{
						$rStack->push($top);
						$rStack->push($value);
					}
				}
			}
		}
	}

	/**
	 * 后缀表达式求值
	 *
	 * @return void
	 * @author zhiliang
	 **/
	public function run()
	{
		return $this->re;
	}
}

$exp = "9123+(3-1)*3+10/2";
$rpn = new rpn($exp);
echo "<pre>";
$e = $rpn->run();
foreach ($e as $key => $value) {
	var_dump($key,$value);
}
