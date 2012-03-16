/**
 * @author David Sichau
 */
$(function() {

	var filterId, paramId, allFields;

	//updates the input files
	function update() {
		filterId = $('"#del_filter #filter_selector');
		allFields = $([]).add(filterId);
	}

	//dialog box for adding deleting parameter
	$("#del_filter").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Delete Filter" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(filterId.val() == -1) {
					bValid = false;
					filterId.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.filters.delFilter(filterId.val());
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

	// generate the html with the filter selector
	function generateHTML() {
		var html = '<p>';
		html += '	Select the Filter to delete:';
		html += '</p>';
		html += '<p><label>filterIdentifier:</label> <select name="filter_selector" id="filter_selector">';
		html += '<option value="-1">choose your filter</option>'
		$.each(completeFilter.filters.getJSON(), function() {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if(index == 'filterIdentifier') {
						html += '	<option value="' + id + '">' + value + '</option>'
					}
				});
			});
		});
		html += '</select></p><p id="param_chooser"></p>';
		return html;
	}

	// open dialog with the new parameter file
	$('#showFilters #delFilter').live('click', function() {
		var html_ = generateHTML();
		$('#del_filter').html(html_);
		update();

		$(function() {
			$("#del_filter").dialog("open");
		});
	});
});
