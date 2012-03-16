/**
 * @author David Sichau
 */
$(function() {

	var filterIdentifier, paramIdentifier, param, allFields, tips;

	//updates the input files
	function update() {
		filterIdentifier = $("#new_param #filterIdentifier");
		paramIdentifier = $("#new_param #paramIdentifier");
		param = $("#new_param #param");
		tips = $("#new_param .validateTips");
		allFields = $([]).add(filterIdentifier).add(paramIdentifier).add(param);
	}

	function updateTips(t) {
		tips.text(t).addClass("ui-state-highlight");
	}

	//dialog box for adding new parameter
	$("#new_param").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Create new Parameters" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(!filterIdentifier.val() || filterIdentifier.val() == -1) {
					bValid = false;
					updateTips("Please choose a filter");
					filterIdentifier.addClass("ui-state-error");
				}
				else if(!paramIdentifier.val()) {
					bValid = false;
					updateTips("Please add a name for the prameter identifier.");
					paramIdentifier.addClass("ui-state-error");
				}
				else if(!param.val()) {
					bValid = false;
					updateTips("Please provide a value for the parameter.");
					param.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.params.addParams(filterIdentifier.val(), paramIdentifier.val(), param.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.params.printJSON("showParams")
			$('#showParams').html(html_);
		}
	});

	function generateHTML() {
		var html = '';
		html += '	<p class="validateTips">';
		html += '		All form fields are required.';
		html += '	</p>';
		html += '	<form>';
		html += '   <label>filterIdentifier:</label> <select name="filterIdentifier" id="filterIdentifier">';
		html += '   <option value="-1">choose your filter</option>'
		$.each(completeFilter.connections.getJSON(), function() {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if(index == "filterName") {
						html += '	<option value="' + value + '">' + value + '</option>'
					}
				});
			});
		});
		html += '       </select>';
		html += '		<br />';
		html += '		<label>paramIdentifier:</label>';
		html += '		<input type="text" name="paramIdentifier" id="paramIdentifier" value="" class="text ui-widget-content ui-corner-all" />';
		html += '		<br />';
		html += '		<label>param:</label>';
		html += '		<input type="text" name="param" id="param" value="" class="text ui-widget-content ui-corner-all" />';
		html += '	</form>';
		return html
	}

	// open dialog with the new parameter file
	$('#showParams #addParam').live('click', function() {
		var html_ = generateHTML();
		$('#new_param').html(html_);
		update();

		$(function() {
			$("#new_param").dialog("open");
		});
	});
});
