/**
 * @author David Sichau
 */
$(function() {

	var filterIdentifier, paramIdentifier, param, allFields, tips;

	//updates the input files
	function update() {
		filterName = $("#new_pipeline #filterName");
		requestType = $("#new_pipeline #requestType");
		requestRank = $("#new_pipeline #requestRank");
		makeTrace = $("#new_pipeline #makeTrace");
		tips = $("#new_pipeline .validateTips");
		allFields = $([]).add(filterName).add(requestType).add(requestRank).add(makeTrace);
	}

	function updateTips(t) {
		tips.text(t).addClass("ui-state-highlight");
	}

	function isInt(value) {
		return !isNaN(parseInt(value)) && (parseFloat(value) == parseInt(value));
	}

	//dialog box for adding new parameter
	$("#new_pipeline").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Create new Parameters" : function() {
				var bValid = true;

				allFields.removeClass("ui-state-error");
				if(!filterName.val() || filterName.val() == -1) {
					bValid = false;
					updateTips("Please choose a filter");
					filterName.addClass("ui-state-error");
				}
				else if(!requestType.val() || requestType.val() == -1) {
					bValid = false;
					updateTips("Please choose a request Type.");
					requestType.addClass("ui-state-error");
				}
				else if(!requestRank.val() || !isInt(requestRank.val())) {
					updateTips('Enter an Integer for requestRank.');
					bValid = false;
					requestRank.addClass("ui-state-error");
				}
				else if(!makeTrace.val() || makeTrace.val() == -1) {
					bValid = false;
					updateTips('Please chose if you want a trace.');
					makeTrace.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.pipeline.addPipeline(filterName.val(), requestType.val(), requestRank.val(), makeTrace.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.pipeline.printJSON("showPipeline")
			$('#showPipeline').html(html_);
		}
	});

	function generateHTML() {
		var html = '';
		html += '	<p class="validateTips">';
		html += '		All form fields are required.';
		html += '	</p>';
		html += '	<form>';
		html += '   <label>filterName:</label><select name="filterName" id="filterName">';
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
		html += '</select>';
		html += '		<br />';
		html += '		<label>requestType:</label>';
		html += ' 		<select name="requestType" id="requestType"> <option value="-1">choose</option>'
		html += '		<option value="DELETE">Delete</option><option value="UPDATE">Update</option></select>'
		html += '		<br />';
		html += '		<label>requestRank:</label>';
		html += '		<input type="text" name="requestRank" id="requestRank" value="" class="text ui-widget-content ui-corner-all" />';
		html += '		<br />';
		html += '		<label>makeTrace:</label>';
		html += ' 		<select name="makeTrace" id="makeTrace"> <option value="-1">choose</option>'
		html += '		<option value="true">True</option><option value="false">False</option></select>'
		html += '	</form>';
		return html
	}

	// open dialog with the new parameter file
	$('#showPipeline #addPipeline').live('click', function() {
		var html_ = generateHTML();
		$('#new_pipeline').html(html_);
		update();

		$(function() {
			$("#new_pipeline").dialog("open");
		});
	});
});
