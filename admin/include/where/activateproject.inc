<?php
//error_reporting(E_ALL);
//ini_set('display_errors', '1');
if (!$_GET['id']) {
	die('No Project ID Supplied!');
}
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	include('../include_all.php');

	if ($_POST['activating'] == 'yeahimdoingit') {
		$project = new Project;
		$pid = $_GET[id];
		$project->init($pid);
		
		$preid = $project->details['pre_id'];
		$postid = $project->details['post_id'];
		if (is_numeric($pid) AND $pid > 0 AND $postid) {
			$project->init($pid);
			$data = array('status'=>'2');
			$surveydata = array('status'=>'1');
			if ($preid) {
				$pre_survey = new Survey($preid);
				$preresult = $pre_survey->update($surveydata);
				if (!$preresult) {
					$err[] = 'Error Updating Pre-Survey Status';
				}
			}
			if ($postid) {
				$post_survey = new Survey($postid);
				$postresult = $post_survey->update($surveydata);
				if (!$postresult) {
					$err[] = 'Error Updating Post-Survey Status';
				}
			}
		
			$editresult = $project->update($data);
			if (is_array($editresult)) {
				$errors = $editresult;
			} else {
			
				$onload = ' onLoad="self.parent.window.location=\'/admin/manage.php?success=activatedproject\';setTimeout(self.parent.tb_remove(),6000);" ';
			}
			
		}
		if (!$postid) {
			$errors[] = '<h2><center>You must have a post-test survey assigned to this project to activate it!</center></h2>';
			$errors[] = '<center><p><strong><a href="#post-survey" onClick="self.parent.window.location=\'/admin/manage.php?where=create&pid='.$pid.'&step=3\'">Continue to Post-Test Survey Creation</a></strong></p></center>';
		}
	}
}
?>
<html>
<head>
<link href="/admin/style.css" rel="stylesheet" type="text/css" />
</head>
<body <?php echo($onload);?>>
<div class="padded">
<br/>
<center>
<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') { 

	if ($errors) { 
		echo "<div class='errors'>";
		foreach ($errors as $error) {
			echo $error;
		}
		echo "</div>";
	} else {
		echo "<h1><center>Success!<br/>You have activated this project</center></h1>";
	}

} else { ?>
<form action="/admin/manage.php?where=activateproject&lay=ajax&id=<?php echo($_GET[id]);?>" method="post">
<h2><center>Your project will be set to active!</center></h2>
<p>Would you like to start gathering data with this project?</p>
<p><em>Note</em>:You <strong>won't</strong> be able to modify any of the surveys you've associated with this project</p>
<input type="hidden" name="pid" value="<?php echo($_GET[id]);?>" />
<input type="hidden" name="activating" value="yeahimdoingit" />
<input type="submit" value="Yes, Activate This Project!" />
<input type="button" value="Cancel" onClick="self.parent.tb_remove();"/>
</form>
<?php }  ?>
</center>
</div>
</body>
</html>