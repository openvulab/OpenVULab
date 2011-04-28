<?php
/*****************************************************************************
Copyright 2008 York University

Licensed under the Educational Community License (ECL), Version 2.0 or the New
BSD license. You may not use this file except in compliance with one these
Licenses.

You may obtain a copy of the ECL 2.0 License and BSD License at
https://source.fluidproject.org/svn/LICENSE.txt
*******************************************************************************/
?><?php
//ini_set('display_errors','1');
//error_reporting(E_ALL);
	
//session_register('new_survey');
//session_register('last_tab');
//session_register('curr_q');

/* Use this hack to work around how PHP handles session vars.
 * When Register_Globals is on, the value of the global $foo
 * is saved, and $_SESSION['foo'] is ignored.
 * When Register_Globals is off, the global $foo is ignored
 * and $_SESSION['foo'] is saved.
 * By making $_SESSION['foo'] a copy of $foo
 * when reg_glob is on, we can use $_SESSION uniformly
 * from here on, regardless of the INI settings.
 */
if(ini_get('register_globals')) {
	//$_SESSION['project_name']  = $project_name;
	//$_SESSION['new_survey'] = $new_survey;
	//$_SESSION['last_tab']   = $last_tab;
	//$_SESSION['curr_q']     = $curr_q;
}


require ESP_BASE.'admin/sanitize.php';


?>
<h2><?php echo(_('Survey Class Testing')); ?></h2>
<h3>Create Survey</h3>
<?php
if ($_POST) {
	$data = $_POST;
	$id = 'new';
	$survey = new Survey('new',$data);
} else {
?>
<table cellspacing="0" cellpadding="0">
	<tr style="vertical-align: top">
		<td class="right"><strong><?php echo(_('Name')); ?></strong></td>
		<td class="left">
			<?php echo mktext('name', 20, 64, $survey); ?>
			<span class="red"><em><?php echo _('Required'); ?></em></span><br />
			<?php echo(
			_('Survey filename.') .' '.
			_('This is used for all further access to this survey.')
			.' ('. _('no spaces') .', '. _('alpha-numeric only') .')'); ?></td>
			<!-- hardcoded, groups to be managed in other ways -->
			<input type="hidden" name="realm" value="auto" />
	</tr>
	
	<tr><td colspan="2"><hr class="line1" /></td></tr>
	<tr style="vertical-align: top">
		<td class="right"><strong><?php echo(_('Title')); ?></strong></td>
		<td class="left">
			<?php echo mktext('title', 60, 60, $survey); ?>
			<span class="red"><em><?php echo _('Required'); ?></em></span><br />
			<?php echo(_('Title of this survey.') .' '.
			_('This appears at the top of every page of this survey.')
			.' ('. _('free-form, including spaces') .')'); ?>
		</td>
	</tr>
	<tr><td colspan="2"><hr class="line1" /></td></tr>
	<tr style="vertical-align: top">
		<td class="right"><strong><?php echo(_('Subtitle')); ?></strong></td>
		<td class="left">
			<?php echo mktext('subtitle', 60, 128, $survey); ?><br />
			<?php echo(_('Subtitle of this survey.') .' '.
			_('Appears below the title.') .' ('. _('free-form, including spaces'). ')'); ?>
		</td>
	</tr>
	<tr><td colspan="2"><hr class="line1" /></td></tr>
	<tr style="vertical-align: top">
		<td class="right"><strong><?php echo(_('Additional Info')); ?></strong></td>
		<td class="left">
			<?php echo mktextarea('info', 5, 60, 'virtual', $survey); ?><br />
			<?php echo(_('Text to be displayed on this survey before any fields.
(i.e. instructions, background info, etc.)')); ?>
		</td>
	</tr>
	
	
	
	<tr><td colspan="2"><hr class="line1" /></td></tr>
	<tr style="vertical-align: top">
		<td class="right"><strong><?php echo(_('Email')); ?></strong></td>
		<td class="left">
            <?php echo mktext('email', 30, 0, $survey); ?><br />
			<?php echo(_('Sends a copy of each submission to address (or leave blank for no email backup).')); ?></td>
	
	<!-- some gluecode for phpesp compatibility -->
	<input type="hidden" name="auto_num" value="Yes" />
		<input type="hidden" name="theme" value="" />
		<input type="hidden" name="thank_head" value="" />
		<input type="hidden" name="thank_body" value="" />
		<input type="hidden" name="thanks_page" value="" />
	
	</tr>   
      
</table>
		<input type="hidden" name="where" value="surveyclass" />
<input type="submit" />
<?php } ?>