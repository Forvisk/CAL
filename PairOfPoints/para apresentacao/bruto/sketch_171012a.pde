class Point {
  PVector pos;
  
  color cor = color(255,255,255,255);
  
  Point(){
    pos = new PVector((int)random(0.0f, (float)width), (int)random(0.0f, (float)height));
  }
  
  void show(){
    fill(cor);    
    ellipse(pos.x, pos.y, 25, 25);
  }
  
}

ArrayList<Point> pontos = new ArrayList();
int num = 10;
int a1 = 0;
int a2 = 0;

void setup() { 
  size(1920, 1080);
  for (int i = 0; i < num; i++){
    pontos.add(new Point());
  }
  
  frameRate(5);
}

// Distancia
float menorDistancia = Float.MAX_VALUE;
Point p1, p2;

void draw() { 
  strokeWeight(4);
  
  if (p1 != null){
    p1.cor = color(255,255,255,255);
    p2.cor = color(255,255,255,255);
  }
  if (a1 < pontos.size() && a2 < pontos.size()){
      background(51);
      Point atual = pontos.get(a1);
      Point ponto = pontos.get(a2);
      if (ponto != atual){
        atual.cor = color(255,0,255,255);
        ponto.cor = color(0,0,255,255);
        stroke(255, 255, 0);
        line(atual.pos.x, atual.pos.y, ponto.pos.x, ponto.pos.y);
        float dist = PVector.dist(ponto.pos, atual.pos);
        if (dist < menorDistancia){
          menorDistancia = dist;
          p1 = atual;
          p2 = ponto;
        }
      }
      
      if (p1 != null){
        p1.cor = color(255, 0, 0, 255);
        p2.cor = color(255, 0, 0, 255);
        stroke(255, 0, 0);
        line(p1.pos.x, p1.pos.y, p2.pos.x, p2.pos.y);
      }
      
      strokeWeight(0);
      for (Point p : pontos){
        p.show();
      }
      
      atual.cor = color(255,255,255,255);
      ponto.cor = color(255,255,255,255);
      
      a2++;
      
      
    saveFrame("frames/bruto-######.png");
    } else {
      noLoop();
    }
    
  
  if (a2 >= pontos.size()){
    a2 = 0;
    a1++;
  }
  

}