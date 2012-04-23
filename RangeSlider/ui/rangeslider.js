/*
 * jQuery UI Range Slider 0.1
 *
 * Copyright 2011, Andrea Stagi (stagi.andrea<at>gmail.com)
 * Dual licensed under the MIT or GPL Version 2 licenses.
 *
 * An extension for Jquery UI Slider
 *
 * Depends:
 *	jquery.ui.slider.js
 */
(function( $, undefined ) {

$.widget( "ui.rangeslider", $.extend(true, {}, $.ui.slider.prototype, {

	widgetEventPrefix: "slide",

	options: {
        extvalues: null,
        tips: null,
        colors: null,
	},

	_create: function() {

        this._change_values();
        $.ui.slider.prototype._create.call(this);
        this._build_table();

	},

    _change_values: function() {

        var o = this.options;
        o.values = jQuery.makeArray(o.extvalues);
        o.extvalues = jQuery.makeArray(o.extvalues);
        var acc = 0;

        for ( var i = 0 ; i < o.extvalues.length; i += 1 )
        {
            acc += o.extvalues[i]
            o.values[i] = acc;
        }

        o.extvalues.push(o.max - acc);

    },

    _build_table: function() {

        var o = this.options;

        var existingHandles = this.element.find( ".ui-slider-handle" ).addClass( "ui-state-default ui-corner-all" )
        var handle = handle = "<a class='ui-slider-handle ui-state-default ui-corner-all' href='#'></a>";
        var handleCount = ( o.values && o.values.length ) || 1;
        var handles=[];

        var table_constr;
        var valw = 0;
        var cont = "";

        var i = o.values.length;

        var tip;

        this.table = $( "<table class='ui-rangeslider' border=1></table>" );

        table_constr += '<tr>';
        for ( var i = 0 ; i < o.values.length; i += 1 )
        {
            if(i == 0)
                valw = o.values[0];
            else
                valw = o.values[i] - o.values[i-1];

            valw = Math.round((valw / o.max) * 100);

            if(o.contents)
                cont = o.contents[i];

            if(o.tips)
                tip = "title='" + o.tips[i] + "'";
                
            table_constr += '<td id="td' + i + '" ' + tip + ' style="background-color:' + o.colors[i] + ';" width=' + valw + '%>' + cont + '</td>';
        }

        valw = o.max - o.values[o.values.length - 1];
        valw = Math.round((valw / o.max) * 100);

        if(o.tips)
            tip = "title='" + o.tips[i] + "'";

        table_constr += '<td id="td' + i + '" ' + tip + ' style="background-color:' + o.colors[i] + ';" width=' + valw + '%></td>';
        table_constr += '</tr>';

        this.table.html(table_constr);

        this.element.append(this.table);

        this.element.removeClass( "ui-widget-content" );

    },
	
	_slide: function( event, index, newVal ) {
		var otherVal,
			newValues,
			allowed;

        var nextVal = 0;

        if(index == this.options.values.length - 1)
            nextVal = this.options.max;
        else
            nextVal = this.options.values[index + 1];

        var prevVal = 0;

        if(index != 0)
            prevVal = this.options.values[index - 1];

        if(newVal < prevVal)
            return;

        if(newVal > nextVal)
            return; 

        if(newVal == prevVal)
            this.table.find("#td" + (index)).hide();
        else
            this.table.find("#td" + (index)).show();

        if(newVal == nextVal)
            this.table.find("#td" + (index + 1)).hide();        
        else
            this.table.find("#td" + (index + 1)).show();    

        var barVal = 0;

        if(index == 0)
            barVal = newVal;
        else
            barVal = (newVal - prevVal);

		if ( this.options.values && this.options.values.length ) {
			otherVal = this.values( index ? 0 : 1 );
			if ( ( this.options.values.length === 2 && this.options.range === true ) && 
					( ( index === 0 && newVal > otherVal) || ( index === 1 && newVal < otherVal ) )
				) {
				newVal = otherVal;
			}

			if ( newVal !== this.values( index ) ) {

                newValues = this.values();

                newValues[ index ] = newVal;

                for ( var i = index ; i < index + 2; i += 1 )
                {
                    if(i != 0)
                        this.options.extvalues[i] = newValues[i] - newValues[i-1];
                    if(i == this.options.extvalues.length - 1)
                        this.options.extvalues[i] = this.options.max - newValues[i-1];
                    if(i == 0)
                        this.options.extvalues[i] = newValues[i];
                }

				newValues = this.options.extvalues;
                
				allowed = this._trigger( "slide", event, {
					handle: this.handles[ index ],
					value: newVal,
					values: newValues
				} );
				otherVal = this.values( index ? 0 : 1 );
				if ( allowed !== false ) {
					this.values( index, newVal, true );
				}

			}

		} else {
			if ( newVal !== this.value() ) {
				allowed = this._trigger( "slide", event, {
					handle: this.handles[ index ],
					value: newVal
				} );
				if ( allowed !== false ) {
					this.value( newVal );
				}
			}
		}

        //TODO Optimize it like there's no tomorrow

        var td1, td2;

        td1 = Math.round((this.options.extvalues[index] / this.options.max) * 100);
        td2 = Math.round(((this.options.extvalues[index + 1]) / this.options.max ) * 100);

        var table_w = 0;

        for(var i = 0; i < this.options.extvalues.length; i += 1 )
            if(i != index && i != index + 1)
                table_w += parseInt(this.table.find("#td" + i).attr("width").replace('%', ''));

        table_w += td1 + td2;
        console.log(table_w);

        if(table_w > 100)
            td1 = td1 + (100 - table_w) ;

        if(table_w < 100)
            td1 = td1 + (100 - table_w) ;

        this.table.find("#td" + index).attr("width", "" + td1 + "%");
        this.table.find("#td" + (index + 1)).attr("width", "" + td2 + "%");

	},

	_stop: function( event, index ) {
		var uiHash = {
			handle: this.handles[ index ],
			value: this.value()
		};
		if ( this.options.values && this.options.values.length ) {
			uiHash.value = this.values( index );
			uiHash.values = this.values();
		}

		this._trigger( "stop", event, uiHash );
	},

	_change: function( event, index ) {
		if ( !this._keySliding && !this._mouseSliding ) {
			var uiHash = {
				handle: this.handles[ index ],
				value: this.value()
			};
			if ( this.options.values && this.options.values.length ) {
				uiHash.value = this.values( index );
				uiHash.values = this.values();
			}

			this._trigger( "change", event, uiHash );
		}
	},

	range_values: function( index, newValue ) {
        return this.options.extvalues[ index ];
    },

}));

}(jQuery));
