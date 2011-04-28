/*
$(document).ready(function(){
    doProcessSelectBox($("#type_id"));
    $('#length_col').show();
    $('#precision_col').show();
});
*/


function doProcessSelectBox(box)
{
    var lengthtips = {
        2:"Specify the size of a textbox.",
        3:"Specify the number of columns(width) of the essay box.",
        5:"The minimum number of checkboxes that must be checked in order to proceed (default 0).",
        8:"Specify the upper end of the scale(ie '5' would produce a scale from 1 to 5).",
        10:"Specify the maximum number of digits."
    };

    var precisiontips = {
        2:"The maximum number of characters in the textbox.",
        3:"Specify the number of rows(height) of the essay box",
        8:"Set this to 1 in order to add an N/A column."
    };
    var id = box.value;
    if (!(id == 4 || id == 5 || id == 6 || id == 8)){
            $('#multichoice').hide();
    }
    else{
            $('#multichoice').show();
    }

    if(!(id == 2 || id == 3 || id == 5 || id == 8 || id == 10)){
        $('#length_col').hide();
    }
    else{
        $('#length_col').show();
        document.getElementById("length_tip").innerHTML = lengthtips[id];
    }

    if(!(id == 2 || id == 3 )){
        $('#precision_col').hide();
    }
    else{
        $('#precision_col').show();
        document.getElementById("precision_tip").innerHTML = precisiontips[id];
    }
}



window.onload = function(){
    doProcessSelectBox(document.getElementById("type_id"));
};


