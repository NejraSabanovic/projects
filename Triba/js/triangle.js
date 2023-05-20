
let canvas = document.getElementById("myCanvas");
let ctx = canvas.getContext("2d");

		
		let canvasHeight = canvas.height;
		let canvasWidth = canvas.width;

		console.log(canvasHeight,canvasWidth)
		
		ctx.fillStyle = "#000200";
		ctx.fillRect(0,0,canvasWidth * canvasWidth,canvasHeight * canvasHeight);

		var player1 = localStorage.getItem("player1");
		var player2 = localStorage.getItem("player2");

		console.log(player1,player2);
		
		//Classes 

		class Point{
	
			constructor(x,y,r,color){
				this.x = x;
				this.y = y;
				this.r = r;
				this.color = color
			}


			draw(ctx){

				ctx.beginPath();
				ctx.arc(this.x,this.y,this.r,0,Math.PI * 2);
				ctx.fillStyle = this.color;
				ctx.strokeStyle = this.color;
				ctx.fill();
				ctx.stroke;
				ctx.closePath();
			}

			changeColor(newColor){
				this.color = newColor;
				this.draw(ctx);

			}

			isPointClicked(x1,y1){
				const distance = Math.sqrt((x1 - this.x) **2 + (y1 - this.y)**2);

				if(distance < this.r)
					return true;
				
				else
					return false;
				}
			
			
			
		}

		class Triangle{
			constructor(x1,y1,x2,y2,x3,y3,boja) {
                this.x1 = x1;
                this.y1 = y1; 
                this.x2 = x2; 
                this.y2 = y2;
                this.x3 = x3;
                this.y3 = y3;
                this.boja = boja;
            }

            drawTriangle(ctx){
                ctx.beginPath();
                ctx.lineWidth = 2;
                ctx.strokeStyle = this.boja;

                ctx.moveTo(this.x1,this.y1);
                ctx.lineTo(this.x2,this.y2);
                ctx.lineTo(this.x3,this.y3);
                ctx.lineTo(this.x1,this.y1);

                ctx.closePath();
                ctx.stroke();

				pointsOnLine(this.x1,this.y1,this.x2,this.y2);
				pointsOnLine(this.x2,this.y2,this.x3,this.y3);
				pointsOnLine(this.x3,this.y3,this.x1,this.y1);
            }

            oboji(novaBoja){
                this.boja = novaBoja;
                this.drawTriangle(ctx);
        	}


		}

		class Line{
			constructor(x1,y1,x2,y2,color){
				this.x1 = x1;
				this.y1 = y1;
				this.x2 = x2;
				this.y2 = y2; 
				this.color = color;
			}

			drawLine(ctx){
				
				ctx.beginPath();
                ctx.lineWidth = 2;
                ctx.strokeStyle = this.color;

                ctx.moveTo(this.x1,this.y1);
                ctx.lineTo(this.x2,this.y2);
				ctx.closePath();
                ctx.stroke();


			}
			
			changeColor(newColor){
				this.color = newColor;
				this.drawLine(ctx);
			}

		}

		class Vertex{
			constructor(x1,y1,x2,y2){
				this.x1 = x1;
                this.y1 = y1; 
                this.x2 = x2; 
                this.y2 = y2;
			}


		}

		//checking orientation of three points, later used in intersection

		function orientationOfthreePoints(x1,y1,x2,y2,x3,y3){
			let p = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
				if(p > 0) return -1;
				else if(p < 0) return 1;
				else return 0;


		}
		

		// intersection of two vertices

		function isItIntersection(x1,y1,x2,y2,x3,y3,x4,y4){
			
			let o1 = orientationOfthreePoints(x1,y1,x2,y2,x3,y3);
			let o2 = orientationOfthreePoints(x1,y1,x2,y2,x4,y4);
			let o3 = orientationOfthreePoints(x3,y3,x4,y4,x1,y1);
			let o4 = orientationOfthreePoints(x3,y3,x4,y4,x2,y2);

			if(o1 != o2 && o3 != o4)
				return true;

			return false;
			
		}

		function vertexIntersection(x1,y1,x2,y2,vertices){

			for (var i = 0;i<vertices.length;i++){

				if (isItIntersection(x1,y1,x2,y2,vertices[i].x1,vertices[i].y1,vertices[i].x2,vertices[i].y2)
					|| isItIntersection(x1,y1,x2,y2,vertices[i].x1,vertices[i].y1,vertices[i].x2,vertices[i].y2)
					|| isItIntersection(x1,y1,x2,y2,vertices[i].x1,vertices[i].y1,vertices[i].x2,vertices[i].y2))

					return true;
				
			}

			return false;
	
		}

		//check if points are collinear 

		function collinearPoints(x1,y1,x2,y2,x3,y3){
			let o1 = orientationOfthreePoints(x1,y1,x2,y2,x3,y3);

			if(o1 == 0)
				return true;
			else
			 	return false;
		}


		function canFormTriangle(a,a1,b,b1){

			for(let i = 0; i < triangles.length;i++){

				let triangle = triangles[i];
				let c = triangle.x1;
				let c1 = triangle.y1;
				let d = triangle.x2;
				let d1 = triangle.y2;
				let e = triangle.x3;
				let e1 = triangle.y3;

				if(orientationOfthreePoints(a,a1,b,b1,c,c1) != orientationOfthreePoints(a,a1,b,b1,d,d1)
				&& orientationOfthreePoints(c,c1,d,d1,a,a1) != orientationOfthreePoints(c,c1,d,d1,b,b1)){
					return false;
				}
				if(orientationOfthreePoints(a,a1,b,b1,d,d1) != orientationOfthreePoints(a,a1,b,b1,e,e1)
				&& orientationOfthreePoints(d,d1,e,e1,a,a1) != orientationOfthreePoints(d,d1,e,e1,b,b1)){
					return false;
				}
				if(orientationOfthreePoints(a,a1,b,b1,c,c1) != orientationOfthreePoints(a,a1,b,b1,e,e1) 
				&& orientationOfthreePoints(c,c1,e,e1,a,a1) != orientationOfthreePoints(c,c1,e,e1,b,b1)){
					return false;
				}

			}
			return true;

		}
		

		let points = []; //points will become matrix of storing all points from canvas

		var buttonId = localStorage.getItem("buttonId"); //getting information of which board is selected
		 
		if (buttonId == "myButton1") {
			firstBoard(points);
		} 
		else if(buttonId == "myButton2") {
	
			secondBoard(points);
		}
		else if(buttonId == "myButton3"){

			thirdBoard(points);
		}
		else{

			fourthBoard(points);
			
		}


		//functions for creating boards

		function firstBoard(points){


			for (var i = 0;i < 5; i++) {
				let row = [];
				for(var j = 0;j < 5;j++){
					row.push(null);
				}
				points.push(row);
			}

			const cellSize = 70;

			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){

					const x = (j+1.65) * cellSize;
				    const y = (i+1.45) * cellSize;
				    const r = 10;
				   

					let newPoint = new Point(x,y,r,"#830A4F");
					newPoint.draw(ctx);
					points[i][j] = newPoint;

				}
			}
		}
		
	


		function secondBoard(points){

			for (var i = 0;i < 8; i++) {
				let row = [];
				for(var j = 0;j < 8;j++){
					row.push(null);
				}
				points.push(row);
			}

			const cellSize = 50;

			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){

					const x = (j+1.5) * cellSize;
				    const y = (i+1.5) * cellSize;
				    const r = 10;
				   

					let newPoint = new Point(x,y,r,"#830A4F");
					newPoint.draw(ctx);
					points[i][j] = newPoint;

				}
			}
		}


		function thirdBoard(points){

			for (var i = 0;i < 10; i++) {
				let row = [];
				for(var j = 0;j < 10;j++){
					row.push(null);
				}
				points.push(row);
			}

			const cellSize = 40;

			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){

					const x = (j+1.8) * cellSize;
				    const y = (i+1.7) * cellSize;
				    const r = 10;
				   

					let newPoint = new Point(x,y,r,"#830A4F");
					newPoint.draw(ctx);
					points[i][j] = newPoint;

				}
			}
		}

		function fourthBoard(points){

			let max = 11;
			let min = 2;
			let n = Math.floor(Math.random() * (max -min) ) + min;

			
			for (var i = 0;i < 10; i++) {
				let row = [];
				for(var j = 0;j < n;j++){
					row.push(null);
				}
				points.push(row);
				n = Math.floor(Math.random() * (max -min) ) + min;

			}

			const cellSize = 40;

			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){

					const x = (j+1.8) * cellSize;
				    const y = (i+1.7) * cellSize;
				    const r = 10;
				   

					let newPoint = new Point(x,y,r,"#830A4F");
					newPoint.draw(ctx);
					points[i][j] = newPoint;

				}
			}
		}

		
		
		//making players lines that will signal which player is playing

		let line1 = new Line(10,40,10,canvasHeight-40,"blue");
		let line2 = new Line(canvasWidth-10,40,canvasWidth-10,canvasHeight-40,"blue");
		
		line1.drawLine(ctx);
		line2.drawLine(ctx);
		

		let triTacke = []; //storing three clicked points
		let triangles = []; //storing all created trinagles during game
		let vertices = []; //storing all vertices
		let takenPoints = []; //all points that have been selected
		let freePoints = []; //points who are not selected yet
		let igrac1 = true; //player 1
		let igrac2 = false; //player 2


		// all points marked as free at the beginning 

		console.log(points.length);
		for(var i = 0;i < points.length;i++){
			for(var j = 0;j<points[i].length;j++)
				freePoints.push(points[i][j]);
		}
	
		
		function exist(x){ //checking if point is already clicked

			for(var i = 0;i < takenPoints.length;i++){
				
					if(takenPoints[i].x == x.x && takenPoints[i].y == x.y)
						return true
			}
			return false
		}

		function same(x,y){ //finding same point on canvas

			for(var i = 0;i < takenPoints.length;i++){
				
				if(takenPoints[i].x == x && takenPoints[i].y == y){
					
					return true;
				}
		}
		return false;

		}


		//finding points that are between two clicked points,and are also forming triangle

		function pointsOnLine(x1,y1,x2,y2){
			let p1 = new Point(x1,y1,10,"pink");
			
			let p2 = new Point(x2,y2,10,"pink");

			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){
					if (Math.min(x1, x2) <= points[i][j].x && points[i][j].x <= Math.max(x1, x2)) {
						// Check if the point lies within the y bounds of the segment
						if (Math.min(y1, y2) <= points[i][j].y && points[i][j].y <= Math.max(y1, y2)) {
						// Check if the point is collinear with the segment
						if (orientationOfthreePoints(x1, y1, x2, y2, points[i][j].x, points[i][j].y) == 0) {
							// If all conditions are met, return true
							points[i][j].changeColor("gray");
							if(!exist(points[i][j]))
								takenPoints.push(points[i][j]);
						}
						}
					}
					
				}
				
			}
			
		}		


		function isIntersectingAnyTriangles(tx1,ty1,tx2,ty2,tx3,ty3) { //three points 
			for(var i = 0; i < triangles.length;i++){ 

				//checking intersection with some of already formed triangles, iterating through 
			  
				if (isItIntersection(tx1,ty1,tx2,ty2,triangles[i].x1,triangles[i].y1, triangles[i].x2,triangles[i].y2) || isItIntersection(tx1,ty1,tx2,ty2,triangles[i].x2,triangles[i].y2, triangles[i].x3,triangles[i].y3) || isItIntersection(tx1,ty1,tx2,ty2,triangles[i].x1,triangles[i].y1, triangles[i].x3,triangles[i].y3) ||
			  	  isItIntersection(tx1,ty1,tx3,ty3,triangles[i].x1,triangles[i].y1, triangles[i].x2,triangles[i].y2) || isItIntersection(tx1,ty1,tx3,ty3,triangles[i].x2, triangles[i].y2, triangles[i].x3, triangles[i].y3) || isItIntersection(tx1,ty1,tx3,ty3, triangles[i].x1, triangles[i].y1, triangles[i].x3, triangles[i].y3) ||
				  isItIntersection(tx2,ty2,tx3,ty3,triangles[i].x1,triangles[i].y1, triangles[i].x2,triangles[i].y2) || isItIntersection(tx2,ty2,tx3,ty3,triangles[i].x2, triangles[i].y2, triangles[i].x3, triangles[i].y3) || isItIntersection(tx2,ty2,tx3,ty3, triangles[i].x1, triangles[i].y1, triangles[i].x3, triangles[i].y3)) {
				return true;
			  }
			}
			return false;
		  }
		  
		  
	//function that will determine end of game

	function checkEnd() {
			for (let i = 0; i < freePoints.length - 2; i++) {
			  for (let j = i + 1; j < freePoints.length - 1; j++) {
				for (let k = j + 1; k < freePoints.length; k++) {
				  // Check the orientation of the three points
				  
				  let o = orientationOfthreePoints(freePoints[i].x, freePoints[i].y, freePoints[j].x, freePoints[j].y, freePoints[k].x, freePoints[k].y);
				  if (o != 0) {

					// Check if the triangle formed by the three points intersects with any of the already formed triangles
					if (!isIntersectingAnyTriangles(freePoints[i].x,freePoints[i].y,freePoints[j].x,freePoints[j].y,freePoints[k].x,freePoints[k].y)) {
					  return false;
					}
				  }
				}
			  }
			}
			return true;
		  }

		

		//getting names of players
		var player1 = localStorage.getItem("player1");
		var player2 = localStorage.getItem("player2");
		
		//elements used for setting some text and names during game
		const element = document.getElementById("playerName");
		var element2 = document.getElementById("textPlay");
	
		if(igrac1 == true && igrac2 == false){
			line1.changeColor("green");
			line2.changeColor("blue");
			element.innerHTML = player1;
			
		}
		if(igrac2 == true && igrac1 == false){
			line2.changeColor("green");
			line1.changeColor("blue");
			element.innerHTML = player2;
		}

		//main function for game

		function clickHandler(event) {

			if(igrac1 == true && igrac2 == false){
				line1.changeColor("green");
				line2.changeColor("blue");
				element.innerHTML = player1;
				
			}
			if(igrac2 == true && igrac1 == false){
				line2.changeColor("green");
				line1.changeColor("blue");
				element.innerHTML = player2;
			}

			const rect = canvas.getBoundingClientRect();
			 let x = (event.clientX - rect.left) ;
			 let y = (event.clientY - rect.top) ;


			//checking if point on canvas is clicked
			for(var i = 0;i < points.length;i++){
				for(var j = 0;j < points[i].length;j++){
					if(points[i][j].isPointClicked(x,y) == true){
						
						if(igrac1)
							points[i][j].changeColor("#B2C1F4");
						else
							points[i][j].changeColor("#487DCA");

						triTacke.push(points[i][j]); //storing in array
	
					}
				}
			}

		
			if(triTacke.length == 3){


				if(same(triTacke[0].x,triTacke[0].y) || same(triTacke[1].x,triTacke[1].y) || same(triTacke[0].x,triTacke[0].y)){
					alert("Forming triangle from same edge! Try again");

					for(var i = 0;i<triTacke.length;i++){
						if(same(triTacke[i].x,triTacke[i].y))
							triTacke[i].changeColor("#B2C1F4");
						else
							triTacke[i].changeColor("#830A4F");
					}
					triTacke = [];

					if(igrac1 == true){
						igrac2 = false;
						igrac1 = true;
					}
					else{
						igrac1 = false;
						igrac2 = true;
					}

				}

				//check if checked points are collinear

				if(collinearPoints(triTacke[0].x, triTacke[0].y, triTacke[1].x,triTacke[1].y,triTacke[2].x,triTacke[2].y)){
					alert("Not allowed move!Try again");

					for(var i = 0;i<triTacke.length;i++)
						triTacke[i].changeColor("#830A4F");
					triTacke = [];

					if(igrac1 == true){
						igrac2 = false;
						igrac1 = true;
					}
					else{
						igrac1 = false;
						igrac2 = true;
					}
				}
			


			  else{

					//creating vertices

					let duz1 = new Vertex(triTacke[0].x,triTacke[0].y,triTacke[1].x,triTacke[1].y);
					let duz2 = new Vertex(triTacke[1].x,triTacke[1].y,triTacke[2].x,triTacke[2].y);
					let duz3 = new Vertex(triTacke[2].x,triTacke[2].y,triTacke[0].x,triTacke[0].y);


					if(vertexIntersection(duz1.x1,duz1.y1,duz1.x2,duz1.y2,vertices) 
					|| vertexIntersection(duz2.x1,duz2.y1,duz2.x2,duz2.y2,vertices)
					|| vertexIntersection(duz2.x1,duz2.y1,duz2.x2,duz2.y2,vertices)){

					
						alert("Intersecting with other triangle! Try again");

						for(var i = 0;i<triTacke.length;i++)
						triTacke[i].changeColor("#830A4F");
						

						if(igrac1 == true){
							igrac2 = false;
							igrac1 = true;
						}
						else{
							igrac1 = false;
							igrac2 = true;
						}

						triTacke = [];
					
					}

					if(!canFormTriangle(duz1.x1,duz1.y1,duz1.x2,duz1.y2)
					||!canFormTriangle(duz2.x1,duz2.y1,duz2.x2,duz2.y2)
					|| !canFormTriangle(duz3.x1,duz3.y1,duz3.x2,duz3.y2)){
						
						alert("Intersecting with other triangle edge! Try again");

						for(var i = 0;i<triTacke.length;i++)
						triTacke[i].changeColor("#830A4F");
						

						if(igrac1 == true){
							igrac2 = false;
							igrac1 = true;
						}
						else{
							igrac1 = false;
							igrac2 = true;
						}

						triTacke = []

					}
					else{
						console.log("Creating triangle");
					

						vertices.push(duz1);
						vertices.push(duz2);
						vertices.push(duz3);

						let boja;

						if(igrac1){
							boja = "#B2F3F4";
							

						}
						else if(igrac2){
							boja = "#487DCA";
							
						}

					
						let triangle = new Triangle(triTacke[0].x,triTacke[0].y,triTacke[1].x,triTacke[1].y,triTacke[2].x,triTacke[2].y,boja);
							
							triangles.push(triangle);

						
							triangle.drawTriangle(ctx);
							
							

							if(igrac1 == true){
								igrac2 = true;
								igrac1 = false;

								boja = "#B2F3F4";
								let p1 = triTacke[0];
								p1.changeColor(boja);
								let p2 = triTacke[1];
								p2.changeColor(boja);
								let p3 = triTacke[2];
								p3.changeColor(boja);
							}
							else{
								igrac1 = true;
								igrac2 = false;
								boja = "#487DCA";
								let p1 = triTacke[0];
								p1.changeColor(boja);
								let p2 = triTacke[1];
								p2.changeColor(boja);
								let p3 = triTacke[2];
								p3.changeColor(boja);
							}
							triTacke = [];
								
					}

					for (let i = 0; i < freePoints.length; i++) {
						for (let j = 0; j < takenPoints.length; j++) {
							if(freePoints[i].x  == takenPoints[j].x && freePoints[i].y == takenPoints[j].y){
								freePoints.splice(i, 1);  // remove the element at index i
								  i--;  // decrement i to account for the removed element
								 break;
							}
						}
					}

					if(checkEnd() == true){
						alert("THE END");
						console.log("end");
						if(igrac1 == true ){
							
							element2.innerHTML = "WINNER IS   " + player2 ;
							element.innerHTML = " ";
							
							
						}
						else{
							
							element2.innerHTML = "WINNER IS  " + player1;
							element.innerHTML = " ";
							
						}
						
						
						canvas.removeEventListener("click", clickHandler);
						document.getElementById("playAgain").style.display = "block";
						console.log("removed");
						
							

					}	
					else{
						console.log("not end");
						if(igrac1 == true && igrac2 == false){
							line1.changeColor("green");
							line2.changeColor("blue");
							element.innerHTML = player1;
							
						}
						if(igrac2 == true && igrac1 == false){
							line2.changeColor("green");
							line1.changeColor("blue");
							element.innerHTML = player2;
						}
					}
					
				}
			}
			
		  }


		  
		canvas.addEventListener("click", clickHandler); //event listener
		  
		document.getElementById("playAgain").style.display = "none";

		function again(){
			canvas.addEventListener("click", clickHandler);
			window.location.reload();
			localStorage.setItem("player1", player2);
			localStorage.setItem("player2", player1);
			
			document.getElementById("playAgain").style.display = "none";
		}

		
		  
		  

	
	




		
	
	


