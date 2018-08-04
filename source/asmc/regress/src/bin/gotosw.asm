; v2.22 - .GOTOSW[1|2|3] [.IF <condition>]

	.386
	.model	flat
	.code

	.SWITCH al
	  .CASE 1
		.GOTOSW
		.GOTOSW(2)
		.GOTOSW .IF cl
		.ENDC
	  .CASE 2
		.GOTOSW(1)
		.SWITCH al
		  .CASE 1
			.GOTOSW
			.GOTOSW .IF cl
		  .CASE 2
			.GOTOSW1
			.GOTOSW1 .IF cl
			.ENDC
		  .CASE 3
			.SWITCH al
			  .CASE 1
				.GOTOSW
				.GOTOSW .IF cl
			  .CASE 2
				.GOTOSW1
				.GOTOSW1 .IF cl
			  .CASE 3
				.GOTOSW2
				.GOTOSW2 .IF cl
				.ENDC
			  .CASE 4
				.SWITCH al
				  .CASE 1
					.GOTOSW
					.GOTOSW .IF cl
				  .CASE 2
					.GOTOSW1
					.GOTOSW1 .IF cl
				  .CASE 3
					.GOTOSW2
					.GOTOSW2 .IF cl
				  .CASE 4
					.GOTOSW3
					.GOTOSW3 .IF cl
				  .CASE 5
					.GOTOSW3(1)
					.GOTOSW3(2)
					.ENDC
				.ENDSW
			.ENDSW
		.ENDSW
	.ENDSW

	END
