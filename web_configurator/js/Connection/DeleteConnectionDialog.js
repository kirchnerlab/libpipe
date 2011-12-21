/**
 * @author David Sichau
 */
$(function() {

	var filterId, allFields;

	//updates the input files
	function update() {
		filterId = $('#del_connection #connection_selector');
		allFields = $([]).add(filterId);
	}

	//dialog box for adding deleting parameter
	$("#del_connection").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {

			"Delete Filter Object" : function() {
				var bValid = true;
				allFields.removeClass("ui-state-error");
				if(filterId.val()==-1) {
					bValid = false;
					filterId.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.connections.delConnection(filterId.val());
					$(this).dialog("close");
				}
			},
			Cancel : function() {
				$(this).dialog("close");
			}
		},
		close : function() {
			allFields.val("").removeClass("ui-state-error");
			html_ = completeFilter.connections.printJSON("showConnections")
			$('#showConnections').html(html_);
		}
	});

	// generate the html with the filter selector
	function generateHTML() {
		var html = '<p>';
		html += '	Select the Filter:';
		html += '</p>';
		html += '<p><label>filterIdentifier:</label> <select name="connection_selector" id="connection_selector">';
		html += '<option value="-1">choose your filter</option>'
		$.each(completeFilter.connections.getJSON(), function() {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if(index=="filterName") {
						html += '	<option value="' + id + '">' + value + '</option>'
					}
				});
			});
		});
		html += '</select></p>';
		return html;
	}

	
	// open dialog with the new parameter file
	$('#showConnections #delConnection').live('click', function() {
		var html_ = generateHTML();
		$('#del_connection').html(html_);
		update();

		$(function() {
			$("#del_connection").dialog("open");
		});
	});
});
