<?php
require 'stack.php';
/**
 * 逆波兰算法
 * reverse polish notation
 */
class rpn
{
	private $me,$re;//中缀表达式和后缀表达式的队列

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
	 * 算法描述:遍历中缀表达式，遇数字进队列，
	 * 遇符号，
	 * 		若反括弧，出栈，进队列，
	 *		若正括弧进栈，
	 * 		判断与栈顶符号优先级，不高于栈顶符号的，栈顶元素出栈入队列（与栈内元素依次比较），当前符号进栈
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
					if($top && !in_array('(',array($top,$value)) && ($this->config[$value] <= $this->config[$top]))
					{
						$this->re->enqueue($top);
						while ($d = $rStack->pop()) {
							if(in_array('(',array($top,$value)) || ($this->config[$value] > $this->config[$d]))break;
							$this->re->enqueue($d);
						}
						$rStack->push($value);
					}
					elseif($top != false)
					{
						$rStack->push($top);
						$rStack->push($value);
					}
					else
					{
						$rStack->push($value);
					}
				}
			}
		}
		while ($d = $rStack->pop()) {
			$this->re->enqueue($d);
		}
	}

	/**
	 * 后缀表达式求值
	 *
	 * 算法描述：遍历后缀表达式，遇到数字进栈，遇到符号，出栈两个数字进行运算(顺序为：栈底 运算符 栈顶)，将结果入栈
	 *
	 * @return void
	 * @author zhiliang
	 **/
	public function run()
	{
		$rStack = new stack($this->re->count());
		foreach ($this->re as $value) {
			if(is_numeric($value))
			{
				$rStack->push($value);
			}
			else
			{
				$rightOperand = $rStack->pop();
				$leftOperand = $rStack->pop();
				switch ($value) {
					case '+':
						$result = bcadd($leftOperand, $rightOperand, 10);
						break;
					case '-':
						$result = bcsub($leftOperand, $rightOperand, 10);
						break;
					case '*':
						$result = bcmul($leftOperand, $rightOperand, 10);
						break;
					case '/':
						$result = bcdiv($leftOperand, $rightOperand, 10);
						break;
					default:
						throw new Exception('operator error');
						break;
				}
				$rStack->push($result);
			}
		}
		return $rStack->pop();
	}
}

$exp = "9*(3-1)*3+10/2";
$rpn = new rpn($exp);
echo "<pre>";
echo $e = $rpn->run();

