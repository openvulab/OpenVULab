<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?>
<style type="text/css">
  
  a:hover {background-color: #333;color:#fff;}
  p.link a:hover {background-color: #2B2E21;;color:#fff;}
  p.link a:link span{display: none;}
  p.link a:visited span{display: none;}
  p.link a:hover span {
  position: absolute;
  margin:15px 0px 0px 20px;
  background-color: beige;
  max-width:220px;
  padding: 2px 10px 2px 10px;
  border: 1px solid #C0C0C0;
  font: normal 10px/12px verdana;
  color: #000;
  text-align:left;
  display: block;}
</style>

<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');

/* $Id: questions.inc,v 1.31 2007/12/10 08:24:47 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>

  if(empty($_POST['id']))
  	$_POST['id'] = 0;

	$curr_q =& $_SESSION['curr_q'];
	$sid =& $_SESSION['survey_id'];
	// load current values from DB if $sid exists (in session)
  $id = intval($_POST['id']);

	if (isset($_POST['type_id']))
		$_POST['type_id'] = intval($_POST['type_id']) ?  $_POST['type_id'] : '';
	else
    $_POST['type_id'] = '';

	// update failed, stay on same question
	if(!$updated || isset($_POST['extra_choices'])) {
		$curr_q = $id;
	} else {
		if(isset($_POST['new_question']))
			$curr_q = 0;
		if(isset($_POST['edit_question']))
			$curr_q = $_POST['q_id'];
		if($curr_q<0)
			$curr_q = 1;
	}

	$fields = array('name','type_id','length','precise','required','content','position');
	if($updated && $curr_q) {
		// survey questions exist already
		// load values from DB
		$sql = "SELECT * FROM ".$GLOBALS['ESPCONFIG']['question_table']." WHERE id=${curr_q} AND deleted='N' ORDER BY position";
		$result = execute_sql($sql,"",ADODB_FETCH_ASSOC);
		$question = fetch_row($result);
		db_close($result);
		foreach($fields as $f) {
			$_POST[$f] =& $question[$f];
		}
	} else if ($updated) {
		// adding a new question (possibly because there are no questions yet)
		$curr_q = 0;
		foreach(array('name','length','precise','content','position') as $f) {
			$_POST[$f] = '';
		}
	} else {
		foreach($fields as $f) {
			if(!empty($_POST[$f]))
			    $_POST[$f] = _stripslashes($_POST[$f]);
			else
			    $_POST[$f] = '';
		}
	}
?>
<input type="hidden" name="id" value="<?php echo($curr_q); ?>" />
<p>
	<?php 
	   echo(_('Select a question and click edit, or enter a new question below:'));
	?>
	</p><br />

	<select name="q_id" id="q_id">
<?php
	$i = 1;
	// build array of question IDs
	$sql = "SELECT id,type_id,position,content FROM ".$GLOBALS['ESPCONFIG']['question_table']."
	WHERE survey_id=$sid AND deleted='N' AND type_id != 99
	ORDER BY position";
	$result = execute_sql($sql);
	while( list($qid, $tid, $pos, $content) = fetch_row($result)) {
           $result->MoveNext();
           $dots = "";
           $content = strip_tags($content);
           if (strlen($content) > 30) {
              $dots = "...";
           }
	   if ($qid==$curr_q) {
              echo('<option selected="selected" value="'.$qid.'">'.$i++.'. '.substr($content,0, 30).$dots.'</option>');
	   } else {
              echo('<option value="'.$qid.'">'.$i++.'. '.substr($content,0, 30).$dots.'</option>');
	   }
	}
	db_close($result);
?>
</select>
	
	
	<script type="text/javascript" src="/js/jquery-latest.js"></script>

	<input type="submit" name="edit_question" value="<?php echo(_('Edit Question')); ?>" />
	<?php if ($curr_q) { ?>
		<input type="submit" name="new_question" value="<?php echo(_('New Question')); ?>" />
	<?php } ?>
	<br /><br /> 
	<?php
		if(!$curr_q) {
			echo('<h2>'._('New Question').'</h2>');
		} else
				echo('<em>Please note: Questions can be deleted from the \'Order\' tab</em>'); ?>
	
	<div id="questions_input">
            <div class="fl-container-flex fl-col-flex4 content">
                <br/>
			<!--<th>&nbsp;</th>
			<th><?php echo(_('Question Name')); ?></th>-->
			<div class="fl-col"><p><strong><?php echo(_('Question Type')); ?></strong></p><br/>
                        <?php
				if($updated && empty($_POST['type_id'])) $_POST['type_id'] = 2;
				$sql = 'SELECT id, type FROM '.$GLOBALS['ESPCONFIG']['question_type_table'].' WHERE id != 99';
				$result = execute_sql($sql);
				$arr = array();
				while(list($key, $val) = fetch_row($result)) {
                    			$result->MoveNext();
					$arr["$key"] = _($val);
				}
				$new = 'temp';
				if ($curr_q)
					$new = null;
				echo(mkselect('type_id',$arr,$new,'doProcessSelectBox'));
			?>
                        </div>
                        <div class="fl-col"><p><strong><?php echo(_('Required')); ?>?</strong></p><br/>
                        <?php
				if(empty($_POST['required'])) $_POST['required'] = 'N';
				echo(mkselect("required",array(
					"Y" => _('Yes') . '               ',
					"N" => _('No')
				))); ?>
			</div>
			<div class="fl-col" id="length_col"><p class="link"><strong><?php echo(_('Length')); ?></strong> <a href="#" >(see help)<span id="length_tip">tooltip</span></a></p><br/>
                        <?php
				if(empty($_POST['length'])) $_POST['length'] = 0;
				echo(mktext("length",4));
			?>
                        </div>
			<div class="fl-col" id="precision_col"><p class="link"><strong><?php echo(_('Precision')); ?></strong> <a href="#" >(see help)<span id="precision_tip">tooltip</span ></a></p><br/>
                        <?php
				if(empty($_POST['precise'])) $_POST['precise'] = 0;
				echo(mktext("precise",4));
			?>
                            </div>

	    
		
			<!--<td>&nbsp;</td>
			<td><?php echo(mktext('name',12)); ?></td>-->

                </div>
		<div class="fl-fix fl-container-flex footer">
			<!--<th>Text</th>-->
			<strong>Question:</strong><br />&nbsp;<?php
				echo(mktextarea("content",4,80,"VIRTUAL"));
			?>
		</div>
	</div><br /><br />
<?php
	// has answer options ... so show that part of the form
    $sql = "SELECT has_choices
					FROM ".$GLOBALS['ESPCONFIG']['question_type_table']."
        WHERE id=" . $_POST['type_id'];
    $choices = get_one($sql);
	if($curr_q == 0 ||
            empty($_POST['type_id']) || $choices =='Y') {
		include($GLOBALS['ESPCONFIG']['include_path']."/tab/questions_options".$GLOBALS['ESPCONFIG']['extension']);
	}
?>
<?php if($curr_q) { ?>
	<input type="submit" name="new_question" value="Save Changes"/>
<?php 
} else { ?>
	<input type="reset" value="Clear" /><input type="submit" name="new_question" value="Add Question to Survey"/>
<?php } ?>
