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
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
//Clean up the session vars
unset($_SESSION['renamed']);
//Lets Build Array of All Project's Surveys
//By putting a bogus status in for get_projects_by_owner() we will retrieve ALL projects
$all_projects = get_projects_by($_SESSION['acl']['userid']);
//$all_private_projects = get_projects_by_public("postsurvey","N");
$all_public_projects = get_public_projects("postsurvey");

$records = $all_projects;

for ($done = 0; $done <= 1; $done++) {
    if ($done) {
        $records = $all_public_projects;
    }
    foreach ($records as $aProject) {
        $pname = $aProject->details['name'];
        if ($pname != $project->details['name']) {
            if ($aProject->post_survey) {
                unset($sid);
                $sid = $aProject->post_survey['id'];
                if (!in_array($sid, $all_surveys)) {
                    $all_surveys[$pname]['post'] = $sid;
                }
            }
        }
    }
    if (!$done) {
        $survey_list_html = '';
        //Next ALL Project Surveys
        $survey_list_html .= '------ Your surveys ------';
    } else {
        $survey_list_html .= "<option>------ Public surveys ------</option>\n";
    }
    foreach ($all_surveys as $pname => $survey) {

        foreach ($survey as $type => $sid) {
            if ($project->post_survey['id'] AND $project->post_source != 'new') {
                $selected = "selected='selected'";
            }
            $survey_list_html .= "<option $selected id='survey_option_" . $sid . "' value='" . $sid . "'>Project: " . $pname . " (" . ucwords($type) . "-test)</option>\n";
        }
    }
    $all_surveys = '';
}
$survey_list_html = "<option>Choose a survey</option>\n".$survey_list_html;
////////////////////////////////////////
////////////////////////////////////////
//post-load stuff for Saved Surveys
if (empty($project->post_survey['id'])) {
	$source = "none";
	$notes[] = "A post test survey is <span>required</span>. <span class='green'>Select an option below to create one.</span>";
}
elseif (!empty($project->post_survey['id']))
{
	if ($project->details['post_source'] == 'new') {
		//Set a Default
		$source = 'new';
	} elseif ($project->details['post_source']) {
		$source = 'copy';
		$source_id = $project->details['post_source'];
	}
	
//Load the postvious survey
$post_id = $project->post_survey['id'];
}
//Setup The Survey Options Panel
$checked[$source] = 'checked="checked"';
/*echo "<post>";
	print_r($project);
echo "</post>";*/
?>
<div class="column field_lines">
<h1><?php echo($project->details['name']._(' - post-Test Survey')); ?></h1>
<?php
if (count($notes) > 0) {
	echo "<br /><div class='note'>";
	foreach ($notes as $note) {
		echo "<div>$note</div>";
	}
	echo "</div><br/>";
}
?>
<!--
<h2>Choose:</h2>
<field class="indent1">
	<input type="radio" name="post_choose" value="none" id="post_none" <?php// echo($checked['none']);?> /><label>No post-test survey</label>
</field>

<h3 class="indent1">Create a new survey</h3>
-->
<field class="indent2">
	<input type="radio" name="post_choose" value="new" id="post_new" <?php echo($checked['new']);?> /><label>... from Scratch</label>
</field>

<field style="border-bottom:1px solid #ccc;padding-bottom:5px;width:300px;" class="indent2">
	<input type="radio" name="post_choose" value="copy" id="post_copy" <?php echo($checked['copy']);?>/><label>... from Existing Survey</label>
	<div class="indent">
		<select id="copysurvey" name="copysurvey" >
			<?php echo $survey_list_html; ?>
		</select>
	</div>
</field>

<div id="surveytitle">
<h2><?php echo $project->post_survey['title']; ?></h2>
</div>
<div >
<!-- <div id="surveynote">Survey Changes Will Be Saved After Title is Entered</div> -->
<iframe id="surveytool" style="<?php if ($project->details['post_source']) echo 'display:block;'; ?>" src="manage.php?where=survey_tool&pid=<?php echo($project->id);?>&lay=form&<?php echo ($project->post_survey[id]) ? 'newid='.$project->post_survey[id] : 'new=true'; ?>"></iframe>

</div>
<input type="hidden" name="survey_source" id="survey_source" />
<input type="hidden" name="survey_id" id="survey_id" />
<input type="hidden" name="from" value="3" id="from" />
<input type="hidden" name="go" value="5" id="go" />
<input type="hidden" name="where" value="create" id="where" />
<input type="submit" class="surveytoolsubmit" value="Proceed to Next Step >>>" />
</div>