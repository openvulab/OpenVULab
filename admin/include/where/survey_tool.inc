<?php
/* * ***************************************************************************
  Copyright 2008 York University

  Licensed under the Educational Community License (ECL), Version 2.0 or the New
  BSD license. You may not use this file except in compliance with one these
  Licenses.

  You may obtain a copy of the ECL 2.0 License and BSD License at
  https://source.fluidproject.org/svn/LICENSE.txt
 * ***************************************************************************** */
?><?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
/* $Id: tab.inc,v 1.22 2007/12/03 13:40:55 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>
?><script type="text/css">
    div {padding:5px;}
</script>

<?php
if (!@$survey_processed) {
    include(esp_where("survey_process"));
}


//Serialize $_GET
$get_string = implode_get();
$get_string = '?';
if ($_GET['lay']) {
    $get_string .= '&amp;lay=' . $_GET['lay'];
}
if ($_GET['where']) {
    $get_string .= '&amp;where=' . $_GET['where'];
}

if ($_POST['where']) {
    $where = $_POST['where'];
}
if ($_GET['where']) {
    $where = $_GET['where'];
}
if (!$where) {
    $where = 'survey_tool';
}
//Include Just Html?
?><script type="text/javascript" src="include/tab/<?php echo($tab); ?>.js"></script><?php
if (@$_GET[lay] == 'form' OR $_GET['lay'] == 'full') {
?>

<?php
    if ($_SESSION['survey_id']) {
?>

        <script type="text/javascript">
            <!-- parent.$('#surveynote').html('Survey Changes will be saved.'); -->
            parent.$('#surveynote').css({color: 'green'});
            parent.$('#surveytool').css({border: '2px solid green'});
        </script>
<?php
    }
?>

<script type="text/javascript">
    if (parent.$('#surveytool').css('display') != 'none') {
        parent.$('#surveynote').css({display: 'block'});
    }
</script>
<div id="content" class="fl-container-680" style="padding:15px;">
    <form method="post" id="tabs" onsubmit="isSubmit(); validate();" action="<?php echo($ESPCONFIG['ME']);
        echo $get_string; ?>">
            <?php } //ajax
            ?>
<?php if (!empty($errstr))
            echo(mkerror($errstr) . "<br />\n"); ?>
<?php if ($where != 'survey_tool') { ?>
        <input type="hidden" name="where_sub" value="2" id="where_sub"/>
        <input type="hidden" name="where_context" value="<?php echo(@$where_context); ?>" id="where_context"/>
<?php } ?>  

        <div id="tabmenu" class="fl-container-flex header">
<?php
        if ($_GET['fromID']) {
            $tab = 'preview';
        } else {
 ?>
            <input type="submit" name="tab" value="Survey Info" />
           <!-- <a class="fl-button-left" href="#"><strong class="fl-button-inner">Survey Info</strong></a>-->
            <input type="submit" name="tab" value="Questions" />
            <!--<a class="fl-button-right" href="#"><strong class="fl-button-inner">Questions</strong></a>-->
            <input type="submit" name="tab" value="Order" />
            <!--<a class="fl-button-right" href="#"><strong class="fl-button-inner">Order</strong></a>-->
            <input type="submit" name="tab" value="Preview" />
            <!--<a class="fl-button-right" settings" href="#"><strong class="fl-button-inner">Preview</strong></a>-->

<?php } ?>
        <?php /* Removed:
          <input type="submit" name="tab" value="Conditions" />
          <input type="submit" name="tab" value="Finish" />
         */ ?>
        

  
<?php include($ESPCONFIG['include_path'] . '/tab/' . $tab . $ESPCONFIG['extension']);
        $_SESSION['last_tab'] = $tab; ?>

        <?php if ($tab == 'finish') {
            echo('&nbsp;');
            return;
        } ?>
        <?php if ($_SESSION['new_survey']) {
 ?>
        <?php if (@$_GET[lay] == 'full') {
 ?>
        <?php echo(_('Click cancel to cancel this survey, or click continue to proceed to the next tab.')); ?><br />
                <input type="submit" name="where" value="Cancel" onclick='return cancelConfirm()' />
        <?php if ($tab == 'preview') {
 ?>
                    <input type="submit" name="tab" value="Finish" />
        <?php return;
                } ?>
                <input type="submit" name="tab" value="Continue &gt;" />
                <input type="hidden" name="where" value="<?php echo $where; ?>" id="where"/>
<?php } //not ajax 
?>
        <?php return;
        } ?>
<?php /* echo(_('The survey title and other general fields are on the <strong>General</strong> tab.
          Individual survey questions are added and modified on the <strong>Questions</strong> tab.
          Questions may be re-ordered or deleted from the <strong>Order</strong> tab.
          You may see a preview of your survey at any time, by going to the <strong>Preview</strong>
          tab. If you have no further changes click <strong>Finish</strong> to go back to the
          Management Interface.')); */ ?>
<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
        /*
          <input type="submit" name="tab" value="General" />
          <input type="submit" name="tab" value="Questions" />
          <input type="submit" name="tab" value="Order" />
          <input type="submit" name="tab" value="Conditions" />
          <input type="submit" name="tab" value="Preview" />
          <input type="submit" name="tab" value="Finish" />
         */
?>
<?php if (@$_GET[lay] == 'full') { ?>

<?php } else { //if it IS ajax ?>

                </form>
            </div>
            </body>
            </html>
<?php /* <input type="submit" value="Save Survey"/> */ ?>
<?php } //ajax else  ?>
<?php
        if (strpos($where_context, 'copy')) {
            unset($_SESSION['survey_id']);
        }
?>