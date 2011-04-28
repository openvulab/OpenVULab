<?php
/* * ***************************************************************************
  Copyright 2008 York University

  Licensed under the Educational Community License (ECL), Version 2.0 or the New
  BSD license. You may not use this file except in compliance with one these
  Licenses.

  You may obtain a copy of the ECL 2.0 License and BSD License at
  https://source.fluidproject.org/svn/LICENSE.txt
 * ***************************************************************************** */
?>
<?php
/* $Id: general.inc,v 1.26 2007/07/09 12:58:17 liedekef Exp $ */

/* vim: set tabstop=4 shiftwidth=4 expandtab: */

// Written by James Flemer
// For eGrad2000.com
// <jflemer@alum.rpi.edu>
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
//Find context is available.
unset($sid);

$sid = $_SESSION['survey_id'];
if ($_GET['fromID'] && !$sid) {
    $sid = $_GET['fromID'];
    //$_SESSION['fromID'] = $sid ;
}
// load current values from DB if $sid exists (in session)
$survey = array();
if (!empty($sid) && $updated) {
    $sql = "SELECT * FROM " . $GLOBALS['ESPCONFIG']['survey_table'] . " WHERE id=${sid}";
    $result = execute_sql($sql, "", ADODB_FETCH_ASSOC);
    $survey = fetch_row($result);
    db_close($result);
} else {
    $fields = array('name', 'realm', 'title', 'subtitle', 'email', 'theme', 'thanks_page', 'thank_head', 'thank_body', 'info', 'public', 'auto_num');
    foreach ($fields as $f) {
        if (!empty($_POST[$f]))
            $survey[$f] = _stripslashes($_POST[$f]);
        else
            $survey[$f] = '';
    }
}

//Survey Filenames have been taken out and replaced with a generation and project reference naming schema
// EX. 31_rel_12342341_gen
//     - project id: 31, timestamp = 12342341
// EX. 31_rel_12342341_gen35_rel_55523423_gen
//     - project id: 35, initial project id: 31
//Set Default Surveyname
$key = '_generation_pid_' . $_SESSION['pid'] . '_';
if ($_GET['makenew']) {
    if (strpos($survey['name'], $key) === false) {
        $_SESSION['dupeQuestions'] = '';
        $_SESSION['dupeQuestions'] = $sid;
        if (!$_SESSION['dupeQuestions']) {
            $_SESSION['dupeQuestions'] = $_SESSION['survey_id'];
        }
        //unset($_SESSION['survey_id']);
        //unset($sid);
        //unset($_GET['fromID']);
        $sname = $survey['name'] . time() . $key;
    }
} else {
    $sname = $survey['name'];
}
if (empty($sname)) {
    $sname = time() . $key;
}
/* if (!empty($survey['name'])) {
  //
  if (strpos($survey['name'],$_SESSION['pid']."_rel_") === false) {
  $sname = $survey['name'].$_SESSION['pid']."_rel_".time().$gkey;
  } else {
  $sname = $survey['name'];
  }

  } */
?>
<p><?php echo(_('The information on this tab applies to the whole survey.
Fill out this page then click any button to
edit individual fields.')); ?></p>
<script type="text/javascript">
    <!--
    function validate() {
        return true;
    }
    -->
</script>

<table cellspacing="0" cellpadding="20">
    <tr style="vertical-align: top;display:none;">
        <td><strong><?php echo(_('Name')); ?></strong></td>
        <td>

<?php /* 	<?php echo mktext('name', 20, 64, $survey); ?>
  <span class="red"><em><?php echo _('Required'); ?></em></span><br />
  <?php echo(
  _('Survey filename.') .' '.
  _('This is used for all further access to this survey.')
  .' ('. _('no spaces') .', '. _('alpha-numeric only') .')'); ?></td>
  <!-- hardcoded, groups to be managed in other ways -->
 */ ?>
            <input type="hidden" name="name" value="<?php echo($sname); ?>" />
            <input type="hidden" name="realm" value="auto" /></td>
    </tr>


    <tr style="vertical-align: top">
        <td align="right"><label for="title"><strong><?php echo(_('Title:')); ?></strong></label></td>
        <td>
<?php echo mktext('title', 60, 60, $survey); ?>
            <span class="red"><em><?php echo _('Required'); ?></em></span><br />
<?php
            echo(_('Title of this survey.') . ' ' .
            _('This appears at the top of every page of this survey.')
            . ' (' . _('free-form, including spaces') . ')');
?>
        </td>
    </tr>


    <tr style="vertical-align: top">
        <td align="right"><label for="subtitle"><strong><?php echo(_('Subtitle:')); ?></strong></label></td>
        <td>
<?php echo mktext('subtitle', 60, 128, $survey); ?><br />
<?php echo(_('Subtitle of this survey.') . ' ' .
            _('Appears below the title.') . ' (' . _('free-form, including spaces') . ')'); ?>
        </td>
    </tr>


    <tr style="vertical-align: top">
        <td align="right"><label for="info"><strong><?php echo(_('Additional Info:')); ?></strong></label></td>
        <td>
<?php echo mktextarea('info', 5, 60, 'virtual', $survey); ?><br />
<?php echo(_('Text to be displayed on this survey before any fields.
(i.e. instructions, background info, etc.)')); ?>
        </td>
    </tr>
    <tr style="vertical-align: top">
        <td align="right"><label for="public"><strong><?php echo(_('Public:')); ?></strong></label></td>
        <td>
<?php echo("Yes ".mkradio("PublicSurvey", "Y",$survey)); ?>
<?php echo("No ".mkradio("PublicSurvey", "N",$survey)); ?>
<?php ?>
            <br/>
            <?php echo(_('Make this survey available for use by other researchers')); ?>
        </td>
    </tr>
    <tr>
        <td><strong> <?php echo(_('Fill in the above information and click "Questions" to continue.')); ?></strong>
        </td>
    </tr>



<!-- 	<tr style="vertical-align: top;display:none;">
        <td><strong><?php echo(_('Email')); ?></strong></td>
        <td>
<?php echo mktext('email', 30, 0, $survey); ?><br />
<?php echo(_('Sends a copy of each submission to address (or leave blank for no email backup).')); ?></td>

	some gluecode for phpesp compatibility 
<input type="hidden" name="auto_num" value="Yes" />
        <input type="hidden" name="theme" value="" />
        <input type="hidden" name="thank_head" value="" />
        <input type="hidden" name="thank_body" value="" />
        <input type="hidden" name="thanks_page" value="" />

	</tr>   -->

</table>
