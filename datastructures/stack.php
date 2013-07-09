<?php
//--------------------------------------------------------
// stack 结构体定义
//--------------------------------------------------------

/**
 * stack class ADT
 *
 * @author zhiliang
 **/
class stack
{
	/**
	 * top表示栈顶元素在数组data中的位置
	 * data 存储整个栈的数据
	 */
	private $top;
	private $data;

	private $maxSize;
	/**
	 * undocumented function
	 *
	 * @return void
	 * @author zhiliang
	 **/
	public function __construct($maxSize = 0)
	{
		$this->top = -1;
		$this->maxSize = $maxSize;
		if($maxSize)
		{
			$this->data = new SplFixedArray($maxSize);
		}
		else
		{
			$this->data = array();
		}
	}

	/**
	 * 往栈顶压入一个元素
	 *
	 * @return void
	 * @author zhiliang
	 **/
	public function push($d)
	{
		if($this->maxSize && $this->top >= $this->maxSize - 1) return false;//栈满
		$this->top++;
		$this->data[$this->top] = $d;
		return true;
	}

	/**
	 * 出栈
	 *
	 * @return node value
	 * @author zhiliang
	 **/
	public function pop()
	{
		if($this->top == -1)return false;//栈空
		$ret = $this->data[$this->top];
		unset($this->data[$this->top]);
		$this->top--;
		return $ret;
	}

} // END Stack class