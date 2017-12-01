/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trabalhorsa;

import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

class RSAElement {

     String msgOriginal,
	     msgCifrada;

     BigInteger P;
     BigInteger Q;

     ChavePublica chavePublica;
     ChavePrivada chavePrivada;

     @Override
     public String toString() {
	  return "Mensagem original: " + msgOriginal
		  + "\nMensagem cifrada: " + msgCifrada
		  + "\nP: " + P
		  + "\nQ: " + Q
		  + "\nChave Privada: ( " + chavePrivada.n + ", " + chavePrivada.d + " )"
		  + "\nChave Publica: ( " + chavePublica.n + ", " + chavePublica.e + " )";
     }

}

class ChavePublica {

     BigInteger e, n;

     ChavePublica(BigInteger _n, BigInteger _e) {
	  e = _e;
	  n = _n;
     }
     
     @Override
     public String toString(){
	  return "( e: " + e.toString() + ", n: " + n.toString()+")";
     }
}

class ChavePrivada {

     BigInteger d, n;

     ChavePrivada(BigInteger _n, BigInteger _d) {
	  d = _d;
	  n = _n;
     }
}

/**
 *
 * @author gustavo
 */
public class TrabalhoRSA {

     static BigInteger dois = new BigInteger("2");

     // Porque nao o random normal?
     // Pq o java tem dessas coisas, de deixar as funcoes antigas ainda no codigo.
     // Compatibilidade e.e
     static SecureRandom random = new SecureRandom();

     static BigInteger smallPrimeMult = BigInteger.valueOf(3L * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41);

     // Utilidade 
     public static BigInteger sqrt(BigInteger x) {
	  BigInteger div = BigInteger.ZERO.setBit(x.bitLength() / 2);
	  BigInteger div2 = div;
	  // Loop until we hit the same value twice in a row, or wind
	  // up alternating.
	  while (true) {
	       BigInteger y = div.add(x.divide(div)).shiftRight(1);
	       if (y.equals(div) || y.equals(div2)) {
		    return y;
	       }
	       div2 = div;
	       div = y;
	  }
     }

     // Basicamente o Crivo
     @SuppressWarnings("empty-statement")
     public static long geraPrimoPequeno(long max) {
	  ArrayList<Long> primos = new ArrayList<>();

	  primos.add((long) 2);
	  primos.add((long) 3);

	  long num = 5;
	  int prox = 0;
	  double raiz = 0;

	  do {
	       prox = 0;
	       raiz = Math.sqrt(num);
	       while ((double) primos.get(++prox) < raiz && (num % primos.get(prox)) != 0);

	       if ((double) primos.get(prox) > raiz) {
		    primos.add(num);
	       }

	       num += ((num % 3 == 2) ? 2 : 4);

	  } while (num < max);

	  Random rand = new Random();
	  return primos.get(rand.nextInt(primos.size()));

     }

     public static BigInteger generatePrime(int bitLength) {
	  int magLen = (bitLength + 31) >>> 5;
	  int temp[] = new int[magLen];
	  int highBit = 1 << ((bitLength + 31) & 0x1f);  // High bit of high int
	  int highMask = (highBit << 1) - 1;  // Bits to keep in high int

	  while (true) {
	       // Construct a candidate
	       for (int i = 0; i < magLen; i++) {
		    temp[i] = random.nextInt();
	       }
	       temp[0] = ((temp[0] & highMask) | highBit);  // Ensure exact length
	       temp[magLen - 1] |= 1;  // Make odd if bitlen > 2
	       String numero = Arrays.toString(temp)
		       .replace("-", "")
		       .replace(",", "") //remove the commas
		       .replace("[", "") //remove the right bracket
		       .replace("]", "") //remove the left bracket
		       .replace(" ", "")
		       .trim();
	       System.out.println("Gerado: " + Arrays.toString(temp));
	       System.out.println("String: " + numero);
	       BigInteger p = new BigInteger(numero);
	       System.out.println("E ele tem " + p.bitCount());
	       System.out.println("De um total de " + magLen);

	       // Do cheap "pre-test" if applicable
	       long r = p.remainder(smallPrimeMult).longValue();
	       if ((r % 3 == 0) || (r % 5 == 0) || (r % 7 == 0) || (r % 11 == 0)
		       || (r % 13 == 0) || (r % 17 == 0) || (r % 19 == 0) || (r % 23 == 0)
		       || (r % 29 == 0) || (r % 31 == 0) || (r % 37 == 0) || (r % 41 == 0)) {
		    continue; // Candidate is composite; try another
	       }

	       // Do expensive test if we survive pre-test (or it's inapplicable)
	       if (isPrimo(p)) {
		    return p;
	       }
	  }
     }

     public static boolean isPrimo(BigInteger n) {
	  // Find a and m such that m is odd and this == 1 + 2**a * m
	  BigInteger thisMinusOne = n.subtract(BigInteger.ONE);
	  BigInteger m = thisMinusOne;
	  int a = m.getLowestSetBit();
	  m = m.shiftRight(a);

	  for (int i = 0; i < 50; i++) {
	       // Generate a uniform random on (1, this)
	       BigInteger b;
	       do {
		    b = new BigInteger(n.bitLength(), random);
	       } while (b.compareTo(BigInteger.ONE) <= 0 || b.compareTo(n) >= 0);

	       int j = 0;
	       BigInteger z = b.modPow(m, n);
	       while (!((j == 0 && z.equals(BigInteger.ONE)) || z.equals(thisMinusOne))) {
		    if (j > 0 && z.equals(BigInteger.ONE) || ++j == a) {
			 return false;
		    }
		    z = z.modPow(dois, n);
	       }
	  }
	  return true;
     }

     public static List<String> SplitStrings(String string, int chars) {
	  List<String> parts = new ArrayList<>();
	  int len = string.length();
	  for (int i = 0; i < len; i += chars) {
	       parts.add(string.substring(i, Math.min(len, i + chars)));
	  }
	  return parts;
     }

     /**
      * @param args the command line arguments
      */
     public static void main(String[] args) {
	  // TODO code application logic here
	  TrabalhoRSA trab = new TrabalhoRSA();

	  String toCript = "Estou testando essa coisa legal chamada RSA";
	  //String toCript = "RSA";
	  int bits = 34;

	  List<String> strings = SplitStrings(toCript, 4);
	  List<RSAElement> criptografados = new ArrayList<>();

	  strings.forEach((parte) -> {
	       criptografados.add(trab.criptografa(parte, bits));
	  });

	  String strNormal = "";
	  String strBruto = "";

	  for (RSAElement cript : criptografados) {
	       System.out.println("\n\n***************************");
	       strNormal += trab.descriptografa(cript.msgCifrada, cript.chavePrivada);
	       strBruto += trab.descriptografa(cript.msgCifrada, cript.chavePublica);
	  }
	  System.out.println("Normal: " + strNormal);
	  System.out.println("Forca Bruta: " + strBruto);
     }

     // Criptografa a string s, com uma chave de bits bits :)
     RSAElement criptografa(String s, int bits) {

	  RSAElement elemento = new RSAElement();
	  System.out.println("\n[[****************\n");

	  // Define os BigIntegers que iremos utilizar
	  BigInteger n, d, e, p, q, phi;

	  // **** AQUI QUE VAMOS CRIAR OS BIGINTEGERS JA PRIMOS ****
	  // Argumentos: bitlen, certeza, fonte para os numero aleatorios.
	  p = generatePrime(bits / 2);//new BigInteger(bits / 2, 100, random);
	  q = generatePrime(bits / 2);//new BigInteger(bits / 2, 100, random);

	  System.out.println("P Gerado: " + p);
	  System.out.println("Q Gerado: " + q);

	  n = p.multiply(q);

	  // calcula (p -1) (q -1)
	  phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));

	  // Escolher um inteiro tal que 1 < e < phi, sendo que e e phi sao primos
	  e = new BigInteger(String.valueOf(geraPrimoPequeno(bits)));

	  // BigInteger.gcd e Maximo Divisor Comum
	  while (phi.gcd(e).compareTo(BigInteger.ONE) > 0 && e.compareTo(phi) < 0) {
	       e = e.add(BigInteger.ONE); // Vai somando de 2 em 2. Uma hora vira primo. Confia :p
	  }

	  d = inversoModular(e, phi);
	  System.out.print("d = ");
	  System.out.println(d.toString());

	  /*
	System.out.print("correto = ");
	System.out.println(e.modInverse(phi).toString());
	   */
	  // Agora ja temos todos os numeros calculados
	  BigInteger msgcif = expModular( new BigInteger(s.getBytes()), e, n);
	  //elemento.msgCifrada = new BigInteger(s.getBytes()).modPow(e, n).toString();
	  elemento.msgCifrada = msgcif.toString();
	  elemento.msgOriginal = s;
	  elemento.chavePrivada = new ChavePrivada(n, d);
	  elemento.chavePublica = new ChavePublica(n, e);
	  elemento.P = p;
	  elemento.Q = q;
	  
	  

	  
	  BigInteger msgO = new BigInteger(s.getBytes());
	  //BigInteger msgC = msgO.modPow(e, n);
	  BigInteger msgC = expModular( msgO, e, n);
	  BigInteger msgDC = msgC.modPow(d, n);
	  System.out.println("\nMsg: '" + s
		  + "'\nOrig: " + msgO
		  + "\nMsg C: " + msgC + " = " + msgO + ".modPow(" + e + ", " + n + ");"
		  + "\nMsg DC: " + msgDC + " = " + msgC + ".modPow(" + d + ", " + n + ");"
		  + "\nMsg DC String: " + new String(msgDC.toByteArray())
		  + "\n\n**************]]\n");
	  /*
	  BigInteger meuC = expModular( msgO, e, n);
	  System.out.println("ExpMod meuC = "+meuC.toString());
	  
	  if ( meuC.equals(msgC)){
	       System.out.println("exp modular C ok");
	  }else{
	       System.out.println("Exp modulkar C not ok");
	  }
	  */
	  /*   // para numeros muito grandes não é eficiente
	  BigInteger meuDC = expModular(msgC, d, n);
	  System.out.println("ExpMod meuDC = "+meuDC.toString());
	  if ( meuC.equals(msgC)){
	       System.out.println("exp modular DC ok");
	  }else{
	       System.out.println("Exp modulkar DC not ok");
	  }
	  */
	  
	  
	  //meu = expModular(meu, d, n);
	  //System.out.println("ExpMod meuDC = "+meu.toString());

	  return elemento;
     }

     BigInteger inversoModular(BigInteger e, BigInteger phi) {
	  return modLinSolver(e, BigInteger.ONE, phi);
     }

     BigInteger modLinSolver(BigInteger a, BigInteger b, BigInteger n) {
	  BigInteger[] r = eucl_ext(a, n);
	  BigInteger res;
	  System.out.println("modlinsolver: d: " + r[0].toString());
	  System.out.println("modlinsolver: x: " + r[1].toString());
	  System.out.println("modlinsolver: y: " + r[2].toString());
	  System.out.println((r[0].remainder(b)).toString());
	  if (r[0].remainder(b).equals(BigInteger.ZERO)) {
	       BigInteger x0 = r[1].multiply(b.divide(r[0]).mod(n));
	       for (BigInteger i = BigInteger.ZERO; i.compareTo(r[0]) == -1; i = i.add(BigInteger.ONE)) {
		    //System.out.println( x0.add(i.multiply(n.divide(r[0])).mod(n)).toString());
		    res = (x0.add(i.multiply(n.divide(r[0]))).mod(n));
		    //System.out.println("Tentativa "+i.toString()+": "+res.toString());
		    if (res.compareTo(BigInteger.ZERO) == 1) {
			 return res;
		    }
	       }
	  } else {
	       System.out.println("Sem solucao");
	       return BigInteger.ZERO;
	  }
	  return BigInteger.ZERO;
     }

     BigInteger[] eucl_ext(BigInteger a, BigInteger b) {
	  BigInteger[] res = new BigInteger[3];
	  res[0] = a;
	  res[1] = BigInteger.ONE;
	  res[2] = BigInteger.ZERO;
	  if (b.equals(BigInteger.ZERO)) {
	       return res;
	  }
	  BigInteger[] resl = eucl_ext(b, a.mod(b));

	  res[0] = resl[0];
	  res[1] = resl[2];
	  res[2] = resl[1].subtract((a.divide(b)).multiply(resl[2]));

	  return res;
     }

     BigInteger expModular(BigInteger in, BigInteger exp, BigInteger n) {
	  BigInteger res;
	  //System.out.println(in.toString()+" ^ "+exp.toString()+" mod "+n.toString()/*+" = "*/);
	  BigInteger k = in.mod(n); // (a*b) mod n = [(a mod n)*(b mod n)] mod n
	  res = exp(k, exp);
	  res = res.mod(n);
	  //System.out.println(res.toString());
	  //System.out.println();
	  return res;
     }

     BigInteger exp(BigInteger in, BigInteger exp) {
	  BigInteger res;
	  BigInteger two = BigInteger.ONE;
	  two = two.add(two);
	  
	  //System.out.print("_");
	  ///System.out.println("Exp de "+in.toString()+" ^ "+exp.toString()+" : ");
	  if( exp.compareTo(BigInteger.ONE) < 1){
	       //System.out.println("Chegou a igual ou menor que 1");
	       ///System.out.println(in.toString());
	       return in;
	  }
	  BigInteger[] div = exp.divideAndRemainder(two);
	  if ( div[1].compareTo(BigInteger.ONE) == 0) { // if true is impar
	       //System.out.println(" impar.");
	       exp = exp.subtract(BigInteger.ONE);
	       exp = exp.divide(two);
	       res = exp(in, exp);
	       res = res.multiply(res);
	       res = res.multiply(in);
	  } else {	    // else is par
	       ///System.out.println(" par.");
	       exp = exp.divide(two);
	       res = exp(in, exp);
	       res = res.multiply(res);
	  }
	  //System.out.println(exp.toString()+".");
	  //System.out.print(".");
	  return res;
     }

     // RSAElement contem tudo necessario
     // A chave privada e composta de 'd' e 'n'
     String descriptografa(String msg, ChavePrivada chave) {
	  return new String(new BigInteger(msg).modPow(chave.d, chave.n).toByteArray());
     }

     // Forca Bruta
     // A chave publica e composta de 'n' e 'e'
     String descriptografa(String s, ChavePublica chave) {
	  
	  System.out.println("Chave publica: "+chave);
	  BigInteger possivelP = sqrt(chave.n);
	  System.out.println("Possivel P comeca em " + possivelP);

	  if (possivelP.mod(dois).equals(BigInteger.ZERO)) {
	       possivelP = possivelP.subtract(BigInteger.ONE);
	  }
	  while (!chave.n.mod(possivelP).equals(BigInteger.ZERO) && !possivelP.equals(chave.n)) {

	       possivelP = possivelP.add(dois); // Vai somando de 2 em 2. Uma hora vira primo. Confia :p
	  }

	  System.out.println("P descoberto: " + possivelP);
	  System.out.println("Para n: " + chave.n);

	  BigInteger possivelQ = chave.n.divide(possivelP);
	  System.out.println("Q descoberto: "+possivelQ.toString());
	  BigInteger phi = possivelP.subtract(BigInteger.ONE).multiply(possivelQ.subtract(BigInteger.ONE));

	  // Escolher um inteiro tal que 1 < e < phi, sendo que e e phi sao primos
	  BigInteger e = chave.e;
	  
	  BigInteger d = e.modInverse(phi);

	  System.out.println("D encontrado: " + d);

	  return new String(new BigInteger(s).modPow(d, chave.n).toByteArray());
     }

}
