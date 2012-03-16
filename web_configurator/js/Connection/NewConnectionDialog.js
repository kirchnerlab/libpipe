/**
 * @author David Sichau
 */
$(function() {

	var filterName, filterIdentifier, precursorName, allFields;

	//updates the input files
	function update() {
		filterName = $("#filterName");
		filterIdentifier = $("#filterIdentifier");
		precursorName = $(".precursorName");
		allFields = $([]).add(filterName).add(filterIdentifier).add(precursorName).add($(".precursorPort")).add($(".thisPort"));
	}

	//dialog box for adding new parameter
	$("#new_connection").dialog({
		autoOpen : false,
		width: 'auto',
		modal : true,
		buttons : {
			"Create new Connection" : function() {
				allFields.removeClass("ui-state-error");
				ports = [];
				precursors = [];
				var bValid = true;


				$(".ports").each(function() {
					$(this).find(".precursorPort").each(function() {
						//this is the precursorPort
						if(!this.value) {
							bValid = false;
							$(this).addClass("ui-state-error");
						} else {
							precursorPort_ = this.value;
						}
					});
					$(this).find(".thisPort").each(function() {
						//this is the thisPort
						if(!this.value) {
							bValid = false;
							$(this).addClass("ui-state-error");
						} else {
							thisPort_ = this.value;
						}
					});
					console.log(this);
					$(this).parents("li").each(function() {
						$(this).find(".precursorName").each(function() {
							//this is the precursor
							if(!this.value) {
								bValid = false;
								$(this).addClass("ui-state-error");
							} else {
								precursorName_ = this.value;
	
								ports.push({
									filterName : precursorName_,
									portNameOfFilter : precursorPort_,
									portNameOfThis : thisPort_
								});
							}
						});
					});
				});

				$(this).find(".precursorName").each(function() {
					//this is the precursor without ports
					if(!this.value) {
						bValid = false;
						$(this).addClass("ui-state-error");
					} else {
						precursorName_ = this.value;
						precursors.push({
							precursorName : precursorName_
						})
					}
				});

				console.log(ports);
				console.log(precursors);

				if(!filterIdentifier.val() || filterIdentifier.val() == -1) {
					bValid = false;
					filterIdentifier.addClass("ui-state-error");
				}
				if(!filterName.val()) {
					bValid = false;
					filterName.addClass("ui-state-error");
				}

				if(bValid) {
					completeFilter.connections.addConnection(filterName.val(), filterIdentifier.val(), precursors, ports);
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

	function generateHTML() {
		var html = '';
		html += '	<p class="validateTips">';
		html += '		All form fields are required.';
		html += '	</p><form>';
		html += '       <label>filterName:</label>';
		html += '		<input type="text" name="filterName" id="filterName" class="text ui-widget-content ui-corner-all" />';
		html += '		<br />';
		html += '   <label>identifier:</label> <select name="filterIdentifier" id="filterIdentifier">';
		html += '   <option value="-1">choose your filter</option>'
		$.each(completeFilter.filters.getJSON(), function() {
			$.each(this, function(id) {
				$.each(this, function(index, value) {
					if(index == "filterIdentifier") {
						html += '	<option value="' + value + '">' + value + '</option>'
					}
				});
			});
		});
		html += '       </select>';
		html += '		<br />';
		html += '		<button type="button" id="addPrecursor">Add Precursor</button>';
		html += ' 		<ul class="precursorList"></ul></form>'
		return html
	}

	// open dialog with the new parameter file
	$('#showConnections #addConnection').live('click', function() {
		var html_ = generateHTML();
		$('#new_connection').html(html_);
		update();

		$(function() {
			$("#new_connection").dialog("open");
		});
	});
	function generateHTMLPrecursor() {
		var html = '<li>';
		html += '       <label>Precursor Name:</label>';
		html += '		<input type="text" name="precursorName" class="precursorName text ui-widget-content ui-corner-all" />';
		html += '		<button type="button" id="addPort">Add Port</button><ul class="portList"></ul></li>';
		return html
	}

	function generateHTMLPort() {
		var html = '<li class="ports">';
		html += '       <p><label>Portname of precursor:</label>';
		html += '		<input type="text" name="precursorPort" class="precursorPort text ui-widget-content ui-corner-all" /></p>';
		html += '		<p><label>Portname of this:</label>';
		html += '		<input type="text" name="thisPort" class="thisPort text ui-widget-content ui-corner-all" /></p></li>';
		return html
	}


	$('#addPrecursor').live('click', function() {
		var html_ = generateHTMLPrecursor();
		$('.precursorList').append(html_);
		update();
	});

	$('.precursorList #addPort').live('click', function() {
		var html_ = generateHTMLPort();
		$(this).parent().find('.portList').append(html_);
		update();
	});
});
