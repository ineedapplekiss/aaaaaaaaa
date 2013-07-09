<?php
/**
* 静态单向链表
*/
class StaticLink
{
	/**
	 * 结构描述
	 * array(
	 	firstNode
	 		data
	 		next

	 	node
	 		data
	 		next

	 	lastNode
	 		data
	 		next 0
	 )
	 */
	public $data;

	//--------------------------------------------------------
	// 链表最大长度
	//--------------------------------------------------------
	private $maxSize;

	public function __construct($length = 1000)
	{
		$this->maxSize = $length;
		$this->data = array();
		for ($i=0; $i < $length-1; $i++) {
			$this->data[$i] = array('next'=>$i+1,'data'=>'');
		}
		$this->data[$length-1] = array('next'=>0,'data'=>'');
		return true;
	}

	/**
	 * 获取链表长度
	 *
	 * @return int length
	 * @author zhiliang
	 **/
	public function listLength()
	{
		$i = $this->data[$this->maxSize-1]['next'];
		$j = 0;
		while($i)
		{
			$i = $this->data[$i]['next'];
			$j++;
		}
		return $j;
	}

	/**
	 * 在第$i个元素之前插入$data
	 *
	 * @return boolean
	 * @author zhiliang
	 **/
	public function listInsert($data,$i=1)
	{
		if($i<1 || $i > $this->listLength()+1)return false;

		$newIndex = $this->malloc();
		//给节点赋值
		$this->data[$newIndex]['data'] = $data;

		//找到$i的前一个元素下标
		$k = $this->maxSize-1;
		for ($l=1; $l < $i; $l++) {
			$k = $this->data[$k]['next'];
		}
		$this->data[$newIndex]['next'] = $this->data[$k]['next'];
		$this->data[$k]['next'] = $newIndex;
		return true;
	}

	/**
	 * 删除一个节点
	 *
	 * @param $i是链表的序，不是数组下标
	 * @return void
	 * @author zhiliang
	 **/
	public function listDel($i)
	{
		if($i<1 || $i > $this->listLength())return false;

		//找到$i的前一个元素下标
		$k = $this->maxSize-1;
		for ($l=1; $l < $i; $l++) {
			$k = $this->data[$k]['next'];
		}
		$listIndex = $this->data[$k]['next'];//找到要释放的数组下标

		$this->data[$k]['next'] = $this->data[$listIndex]['next'];
		$this->free($listIndex);
		$this->data[$listIndex]['data'] = '';
		return true;
	}


	/**
	 * 分配空闲的节点
	 *
	 * @return node key
	 * @author zhiliang
	 **/
	private function malloc()
	{
		$i = $this->data[0]['next'];

		if($this->data[0]['next'])
		{
			$this->data[0]['next'] = $this->data[$i]['next'];
		}
		return $i;
	}

	/**
	 * 释放一个节点
	 *
	 * @return void
	 * @author zhiliang
	 **/
	private function free($i)
	{
		$this->data[$i]['next'] = $this->data[0]['next'];
		$this->data[0]['next'] = $i;
	}
}
echo "<pre>";
$slink = new StaticLink(1000);
print($slink->listLength());
$slink->listInsert("aaa");
$slink->listInsert("bbb");
$slink->listInsert("ccc",2);
$slink->listInsert("dddd",2);

$slink->listDel(2);
print_r($slink->data);