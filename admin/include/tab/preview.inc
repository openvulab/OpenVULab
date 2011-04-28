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
<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
/* $Id: preview.inc,v 1.17 2007/11/27 10:24:34 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>
	unset($sid);
	
	$sid = $_SESSION['survey_id'];
	if ($_GET['fromID'] && !$sid) { 
		$sid = $_GET['fromID'];
	}
	//$sid = _addslashes($_SESSION['survey_id']);
	//$sid = $_SESSION['survey_id'];
	$sql = "SELECT COUNT(*) FROM ".$GLOBALS['ESPCONFIG']['question_table']." WHERE survey_id=${sid}
	AND deleted='N' AND type_id='99'";
	$result = execute_sql($sql);
	$num_sections = 1 + $result->fields[0];
	db_close($result);

	if(empty($_POST['section']))
		$_POST['section']=1;
?>

<p>
<?php echo(_('This is a preview of how this survey will look.
The survey will use the background
color of the document in which it is embedded. If you have no
further changes click <strong> proceed to the next step</strong> below.<br />'));
$pid = $_SESSION['pid'];
if ($_GET['fromID']) { 
	echo "<h2><a href='?where=confirmcopysurvey&lay=ajax&pid=$pid&sid=$sid&KeepThis=true&TB_iframe=true&height=200&width=450' style='color: red' class='thickbox' title='Are you sure you want to use this survey?'>Use/Edit this Survey</a></h2>";
	//survey_copy($sid);
}
?></p>
<?php	if($num_sections > 1) { ?>
<br /><strong><?php echo(_('Section')); ?>:</strong>
<?php		for($i=0;$i<$num_sections;$i++) {	?>
<input type="submit" name="section" value="<?php echo($i+1); ?>" />
<?php		}
	} ?>
<!--<input type="hidden" name="where" value="tab" />
<input type="hidden" name="old_tab" value="preview" />-->
<?php // lets make the css style available during the preview.
      // this should really go into the head section.....but should still work
        $sql = "SELECT theme FROM ".$GLOBALS['ESPCONFIG']['survey_table']." where id = ${sid}";
        if ($result = execute_sql($sql)) {
                if (record_count($result) > 0) {
                        list($css_file) = fetch_row($result);
                        db_close($result);
                     //   echo("<link rel=\"stylesheet\" href=\"".$GLOBALS['ESPCONFIG']['css_url'].$css_file."\"  type=\"text/css\">\n");
                        }
        }
?>
</div>
<div class="fl-container-flex fl-col-mixed content">

<?php
	survey_render($sid,$_POST['section']);
#	if ($ESPCONFIG['auth_response']) {
#		if ($_POST['section'] > 1) {
#        	echo('<input type="button" value="' . _('Previous Page'). '" /> ');
#        }
#	    echo ('<input type="button" value="'. _('Save') .'" /> ');
#	}
#	if($_POST['section'] != $num_sections) {
#		echo('<input type="button" value="'. _('Next Page') .'" /> ');
#	} else {
#		echo('<input type="button" value="'. _('Submit Survey') .'" />');
#	}
?>
	
</div>

<p><!--<a href="#" onclick="window.parent.tb_remove(); return false">Continue</a>-->
</p>
<?php
if ($_GET['fromID']) { 
	echo "<h2><a href='?where=confirmcopysurvey&lay=ajax&pid=$pid&sid=$sid&KeepThis=true&TB_iframe=true&height=200&width=450' style='color: red' class='thickbox' title='Are you sure you want to use this survey?'>Use/Edit this Survey</a></h2>";
	//survey_copy($sid);
}
?>

</div>