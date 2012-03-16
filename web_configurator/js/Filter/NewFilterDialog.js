/**
 * @author David Sichau
 */
$(function() {

	var filterIdentifier, algorithmName, managerName, allFields;

	//updates the input files
	function update() {
		filterIdentifier = $("#new_filter #filterIdentifier");
		algorithmName = $("#new_filter #algorithmName");
		managerName = $("#new_filter #managerName");
		allFields = $([]).add(filterIdentifier).add(algorithmName).add(managerName);
	}

	//dialog box for adding new parameter
	$("#new_filter").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Create new Filter" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(!filterIdentifier.val()) {
					bValid = false;
					filterIdentifier.addClass("ui-state-error");
				}
				if(!algorithmName.val()) {
					bValid = false;
					algorithmName.addClass("ui-state-error");
				}
				if(!managerName.val()) {
					bValid = false;
					managerName.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.filters.addFilter(filterIdentifier.val(), algorithmName.val(), managerName.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.filters.printJSON("showFilters")
			$('#showFilters').html(html_);
		}
	});

	function generateHTML() {
		var html = '';
		html += '	<p class="validateTips">';
		html += '		All form fields are required.';
		html += '	</p>';
		html += '	<form>';
		html += '		<label>filterIdentifier:</label>';
		html += '		<input type="text" name="filterIdentifier" id="filterIdentifier" class="text ui-widget-content ui-corner-all" />';
		html += '		<br />';
		html += '		<label>algorithmName:</label>';
		html += '		<input type="text" name="algorithmName" id="algorithmName" value="" class="text ui-widget-content ui-corner-all" />';
		html += '		<br />';
		html += '		<label>managerName:</label>';
		html += '		<input type="text" name="managerName" id="managerName" value="" class="text ui-widget-content ui-corner-all" />';
		html += '	</form>';
		return html
	}

	// open dialog with the new parameter file
	$('#showFilters #addFilter').live('click', function() {
		var html_ = generateHTML();
		$('#new_filter').html(html_);
		update();

		$(function() {
			$("#new_filter").dialog("open");
		});
	});
});
