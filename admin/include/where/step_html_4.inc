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
<script type="text/javascript">
$(document).ready(function() {
	$("a[href='#activate']").click(function() {
		$("input[name='activate']").attr('value','true');
		$("a[href='#activate'] span").attr('class','green');
		$("a[href='#later'] span").attr('class','grey');
		$('#activate_continue').fadeIn();
	});
	$("a[href='#later']").click(function() {
		$("input[name='activate']").attr('value','false');
		$("a[href='#activate'] span").attr('class','grey');
		$("a[href='#later'] span").attr('class','green');
		$('#activate_continue').fadeOut();
	});
	
	$("a[href='#active']").click(function() {
		$("a[href='#active']").removeClass('grey');
		$("a[href='#inactive']").addClass('grey');
		$("#inactive").fadeOut('fast');
		$("#activating").fadeIn();
		$("#inactivelink").html('');
	});
});
</script>
<div class="column" style="margin-left:50px;">
<h1 style="text-align:center !important;">Activate "<?php echo $project->details[name]; ?>"</h1>
<div class="note margined" id="activating">
	<div>This means your project will <span>now be available to the public</span> and your project will be able to capture data</div>
	<div>Note: You will <strong>NOT</strong> be able to edit the surveys associated with this project</div>
</div>
<div class="margined warn" id="inactive">
	<div>This project is <strong>not</strong> currently active!</div>
	<div><em>Note:</em> This project will not be available to receive any study results and will need to be activated before any data can be collected</div>
</div>
<div style="padding:15px;">
<?php /*<input type="checkbox" id="pend_toggle" <?php echo($checked[end]);?>/>&nbsp;No specified end date.<br />
<strong>Select End Date:</strong>
	<select id="eselectMonth"><option value="01">Jan</option><option value="02">Feb</option> 
    <option value="03">Mar</option><option value="04">Apr</option> 
    <option value="05">May</option><option value="06">Jun</option> 
    <option value="07">Jul</option><option value="08">Aug</option> 
    <option value="09">Sep</option><option value="10">Oct</option> 
    <option value="11">Nov</option><option value="12">Dec</option></select> 
<select id="eselectDay"><option value="01">1</option><option value="02">2</option> 
    <option value="03">3</option><option value="04">4</option> 
    <option value="05">5</option><option value="06">6</option> 
    <option value="07">7</option><option value="08">8</option> 
    <option value="09">9</option><option value="10">10</option> 
    <option value="11">11</option><option value="12">12</option> 
    <option value="13">13</option><option value="14">14</option> 
    <option value="15">15</option><option value="16">16</option> 
    <option value="17">17</option><option value="18">18</option> 
    <option value="19">19</option><option value="20">20</option> 
    <option value="21">21</option><option value="22">22</option> 
    <option value="23">23</option><option value="24">24</option> 
    <option value="25">25</option><option value="26">26</option> 
    <option value="27">27</option><option value="28">28</option> 
    <option value="29">29</option><option value="30">30</option> 
    <option value="31">31</option></select> 
<select id="eselectYear"><option value="2001">2001</option><option value="2002">2002</option> 
    <option value="2003">2003</option><option value="2004">2004</option> 
    <option value="2005">2005</option><option value="2006">2006</option> 
    <option value="2007">2007</option><option value="2008">2008</option> 
    <option value="2009">2009</option><option value="2010">2010</option></select> 
</div>-->*/ ?><br />
<h2><center>Current Status: <span id="inactivelink">Inactive</span> <br /><br /><span id="activelink"><!--<a href="#active" class="grey">Active</a>-->
        <a href="?where=activateproject&amp;lay=ajax&amp;id=<?php echo($project->id);?>&amp;KeepThis=true&amp;TB_iframe=true&amp;height=200&amp;width=450" class="thickbox activatebutton" title="Are you sure you want to activate this project?"><img src="../images/world_go.png" alt="Delete" />Activate Project</a></span></center></h2>
<br />
<div class="left" id="activate_continue" style="clear:both;text-align:left !important;padding:10px;display:none;">
	<input type="submit" value="Click Here to Activate Project!"/><br /><br/>
	<div class="note">
		Note: This cannot be undone, and you will no longer be able to change project fields. <br />
		<strong>You will only be able to manage testers</strong>
	</div>
</div>
<input type="hidden" name="activate" value=""/>
<input type="hidden" name="from" value="4" id="from" />
<input type="hidden" name="go" value="5" id="go" />
<input type="hidden" name="where" value="create" id="where" />
</div>