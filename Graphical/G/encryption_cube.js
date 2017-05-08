0.65//Vertex Shader For Solid Cubes
var S_VSHD_SRC =
'attribute vec4 a_Position;\n' +
'attribute vec4 a_Normal;\n' +
'attribute vec4 a_Color;\n' +
'uniform mat4 u_MvpMatrix;\n' +
'uniform mat4 u_ModelMatrix;\n' +
'uniform mat4 u_NormalMatrix;\n' +
'varying vec4 v_Color;\n' +
'varying vec3 v_Normal;\n' +
'varying vec3 v_Position;\n' +
'void main() {\n' +
'  gl_Position = u_MvpMatrix * a_Position;\n' +
'  v_Position = vec3(u_ModelMatrix * a_Position);\n' +
'  v_Normal = vec3(normalize(u_NormalMatrix * a_Normal));\n' +
'  v_Color = a_Color;\n' +
'}\n';

//Fragment Shader For Solid Cubes
var S_FSHD_SRC =
'#ifdef GL_ES\n' +
'precision mediump float;\n' +
'#endif\n' +
'uniform vec3 u_LightColor0;\n' +
'uniform vec3 u_LightPosition0;\n' +
'uniform vec3 u_LightColor1;\n' +
'uniform vec3 u_LightPosition1;\n' +
'uniform vec3 u_LightColor2;\n' +
'uniform vec3 u_LightPosition2;\n' +
'uniform vec3 u_LightColor3;\n' +
'uniform vec3 u_LightPosition3;\n' +
'uniform vec3 u_AmbientLight;\n' +
'varying vec3 v_Normal;\n' +
'varying vec3 v_Position;\n' +
'varying vec4 v_Color;\n' +
'void main() {\n' +
'  vec3 normal = normalize(v_Normal);\n' +
'  vec3 lightDirection0 = normalize(u_LightPosition0 - v_Position);\n' +
'  vec3 lightDirection1 = normalize(u_LightPosition1 - v_Position);\n' +
'  vec3 lightDirection2 = normalize(u_LightPosition2 - v_Position);\n' +
'  vec3 lightDirection3 = normalize(u_LightPosition3 - v_Position);\n' +
'  float nDotL0 = max(dot(lightDirection0, normal), 0.0);\n' +
'  float nDotL1 = max(dot(lightDirection1, normal), 0.0);\n' +
'  float nDotL2 = max(dot(lightDirection2, normal), 0.0);\n' +
'  float nDotL3 = max(dot(lightDirection3, normal), 0.0);\n' +
'  vec3 diffuse0 = u_LightColor0 * v_Color.rgb * nDotL0;\n' +
'  vec3 diffuse1 = u_LightColor1 * v_Color.rgb * nDotL1;\n' +
'  vec3 diffuse2 = u_LightColor2 * v_Color.rgb * nDotL2;\n' +
'  vec3 diffuse3 = u_LightColor2 * v_Color.rgb * nDotL3;\n' +
'  vec3 ambient = u_AmbientLight * v_Color.rgb;\n' +
'  vec4 color0 = vec4(diffuse0 + ambient, v_Color.a);\n' +
'  vec4 color1 = vec4(diffuse1 + ambient, v_Color.a);\n' +
'  vec4 color2 = vec4(diffuse2 + ambient, v_Color.a);\n' +
'  vec4 color3 = vec4(diffuse3 + ambient, v_Color.a);\n' +
'  gl_FragColor = color0 + color1 + color2 + color3;\n' +
'}\n';

var gX = 0, gY = 6, gZ = 11;
var ang = 0, aX = 0, aY = 5.5, aZ = 10;
var g_last = Date.now();

var a, b, c, d, e, f, g, h, i, j, k, l;
var cubes = [];
var rotate = [];
var prime = true;
var lights = true;

var m = {
    mMatrix: new Matrix4(),    //modelMatrix
    nMatrix: new Matrix4(),    //normalMatrix
    vMatrix: new Matrix4(),    //viewMatrix
    pMatrix: new Matrix4(),    //projMatrix
    mvpMatrix: new Matrix4(),  //mvpMatrix
};

//Main Function
function main() {
    lC();
    cubes[0] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[1] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[2] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[3] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[4] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[5] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[6] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[7] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[8] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[9] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[10] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[11] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[12] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[13] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[14] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[15] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[16] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[17] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[18] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[19] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[20] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[21] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[22] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[23] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[24] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};
    cubes[25] = {mMatrix:new Matrix4(),u:0,v:0,w:0,x:0,y:0,z:0};


    var canvas = document.getElementById('webgl');
    var gl = getWebGLContext(canvas);
    if (!gl) {console.log('Failed WebgL');return;}

    var solid_cube = createProgram(gl, S_VSHD_SRC, S_FSHD_SRC);
    initProgram(gl, solid_cube, 0);
    var Cube = initCube(gl);

    primeCubes(gl, solid_cube);
    m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
    m.pMatrix.setPerspective(90, canvas.width/canvas.height, 0.1, 100);
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(m.mMatrix);

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.clear(gl.COLOR_BUFFER_BIT);

    document.onkeydown = function(ev){
      keydown(ev);};

    var tick = function() {
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        drawCube(gl, Cube, solid_cube);
        requestAnimationFrame(tick);
    };
    tick();
}

//Draw Cube Ojbects
function drawCube(gl, o, program) {
    gl.useProgram(program);
    if (lights == true) {
      gl.uniform3f(program.u_LightColor0, 0.8, 0.8, 0.8);
      gl.uniform3f(program.u_LightColor1, 0.8, 0.8, 0.8);
      gl.uniform3f(program.u_LightColor2, 0.8, 0.8, 0.8);
      gl.uniform3f(program.u_LightColor3, 0.8, 0.8, 0.8);}
    else {
      gl.uniform3f(program.u_LightColor0, 0.0, 0.0, 0.0);
      gl.uniform3f(program.u_LightColor1, 0.0, 0.0, 0.0);
      gl.uniform3f(program.u_LightColor2, 0.0, 0.0, 0.0);
      gl.uniform3f(program.u_LightColor3, 0.0, 0.0, 0.0);}

    initAttributeVariable(gl, program.a_Position, o.vertexBuffer);
    initAttributeVariable(gl, program.a_Normal, o.normalBuffer);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, o.indexBuffer);
    m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(m.mMatrix);
    for (var i = 0; i < cubes.length; i++) {
      primeColorBuffer(gl, program, o, i);
      m.nMatrix.setInverseOf(cubes[i].mMatrix);
      m.nMatrix.transpose();
      m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(cubes[i].mMatrix);
      gl.uniformMatrix4fv(program.u_ModelMatrix, false, cubes[i].mMatrix.elements);
      gl.uniformMatrix4fv(program.u_NormalMatrix, false, m.nMatrix.elements);
      gl.uniformMatrix4fv(program.u_MvpMatrix, false, m.mvpMatrix.elements);
      gl.drawElements(gl.TRIANGLES, o.numIndices, o.indexBuffer.type, 0);
    }
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
}

//Initialize Later Buffer
function initLBuffer(gl, data, num, type) {
  var buffer = gl.createBuffer();   // Create a buffer object
  if (!buffer) {console.log('Failed buffer object');return null;}
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  buffer.num = num;
  buffer.type = type;
  return buffer;
}

//Initialize Attribute Variables
function initAttributeVariable(gl, a_attribute, buffer) {
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.vertexAttribPointer(a_attribute, buffer.num, buffer.type, false, 0, 0);
  gl.enableVertexAttribArray(a_attribute);
}

//Initialize Array Buffers for Later Use
function initArrayBufferForLaterUse(gl, data, num, type) {
  var buffer = gl.createBuffer();   // Create a buffer object
  if (!buffer) {console.log('Failed buffer object');return null;}
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  buffer.num = num;
  buffer.type = type;
  return buffer;
}

//Initialize Element Array Buffers for Later Use
function initElementArrayBufferForLaterUse(gl, data, type) {
  var buffer = gl.createBuffer();　  // Create a buffer object
  if (!buffer) {console.log('Failed buffer object');return null;}
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, data, gl.STATIC_DRAW);
  buffer.type = type;
  return buffer;
}

//Prime Color Buffers for Cubes
function primeColorBuffer(gl, program, o, index) {
  gl.useProgram(program);
  switch (index) {
    default:o.colorBuffer = initLBuffer(gl, o.colors, 3, gl.FLOAT);break;
  }
  initAttributeVariable(gl, program.a_Color, o.colorBuffer);
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, o.indexBuffer);
}

//Set the position, scale, and rotation of all objects in scene.
function primeCubes(gl, program) {
  var u, v, w, x, y, z;
  for (var i = 0; i < cubes.length; i++) {
    switch (i) {
      case 0:u = -2.0625; v = 2.0625; w = -2.0625; x = y = z = 1;break;
      case 1:u = 2.0625; v = 2.0625; w = -2.0625; x = y = z = 1;break;
      case 2:u = 0; v = 2.0625; w = -2.0625; x = y = z = 1;break;
      case 3:u = -2.0625; v = 0; w = -2.0625; x = y = z = 1;break;
      case 4:u = 0; v = 0; w = -2.0625; x = y = z = 1;break;
      case 5:u = 2.0625; v = 0; w = -2.0625; x = y = z = 1;break;
      case 6:u = 0; v = -2.0625; w = -2.0625; x = y = z = 1;break;
      case 7:u = 2.0625; v = -2.0625; w = -2.0625; x = y = z = 1;break;
      case 8:u = -2.0625; v = -2.0625; w = -2.0625; x = y = z = 1;break;

      case 9:u = -2.0625; v = 2.0625; w = 2.0625; x = y = z = 1;break;
      case 10:u = 2.0625; v = 2.0625; w = 2.0625; x = y = z = 1;break;
      case 11:u = 0; v = 2.0625; w = 2.0625; x = y = z = 1;break;
      case 12:u = -2.0625; v = 0; w = 2.0625; x = y = z = 1;break;
      case 13:u = 0; v = 0; w = 2.0625; x = y = z = 1;break;
      case 14:u = 2.0625; v = 0; w = 2.0625; x = y = z = 1;break;
      case 15:u = 0; v = -2.0625; w = 2.0625; x = y = z = 1;break;
      case 16:u = 2.0625; v = -2.0625; w = 2.0625; x = y = z = 1;break;
      case 17:u = -2.0625; v = -2.0625; w = 2.0625; x = y = z = 1;break;

      case 18:u = -2.0625; v = 2.0625; w = 0; x = y = z = 1;break;
      case 19:u = 2.0625; v = 2.0625; w = 0; x = y = z = 1;break;
      case 20:u = 0; v = 2.0625; w = 0; x = y = z = 1;break;
      case 21:u = -2.0625; v = 0; w = 0; x = y = z = 1;break;

      case 22:u = 2.0625; v = 0; w = 0; x = y = z = 1;break;
      case 23:u = 0; v = -2.0625; w = 0; x = y = z = 1;break;
      case 24:u = 2.0625; v = -2.0625; w = 0; x = y = z = 1;break;
      case 25:u = -2.0625; v = -2.0625; w = 0; x = y = z = 1;break;
      default:
    }
    cubes[i].mMatrix.translate(u, v, w);
    cubes[i].x = u;
    cubes[i].y = v;
    cubes[i].z = w;
    cubes[i].mMatrix.scale(x, y, z);
  }
}

//Initialize all program variables for cubes.
function initProgram(gl, program, i) {
    gl.useProgram(program);

    program.a_Position = gl.getAttribLocation(program, 'a_Position');
    program.a_Normal = gl.getAttribLocation(program, 'a_Normal');
    program.u_MvpMatrix = gl.getUniformLocation(program, 'u_MvpMatrix');
    program.u_NormalMatrix = gl.getUniformLocation(program, 'u_NormalMatrix');
  if (i) {}
  else {
    program.a_Color = gl.getAttribLocation(program, 'a_Color');
    program.u_ModelMatrix = gl.getUniformLocation(program, 'u_ModelMatrix');
    program.u_LightColor0 = gl.getUniformLocation(program, 'u_LightColor0');
    program.u_LightPosition0 = gl.getUniformLocation(program, 'u_LightPosition0');
    program.u_LightColor1 = gl.getUniformLocation(program, 'u_LightColor1');
    program.u_LightPosition1 = gl.getUniformLocation(program, 'u_LightPosition1');
    program.u_LightColor2 = gl.getUniformLocation(program, 'u_LightColor2');
    program.u_LightPosition2 = gl.getUniformLocation(program, 'u_LightPosition2');
    program.u_LightColor3 = gl.getUniformLocation(program, 'u_LightColor3');
    program.u_LightPosition3 = gl.getUniformLocation(program, 'u_LightPosition3');
    program.u_AmbientLight = gl.getUniformLocation(program, 'u_AmbientLight');
    gl.uniform3f(program.u_LightPosition0, a, b, c);
    gl.uniform3f(program.u_LightColor0, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightPosition1, d, e, f);
    gl.uniform3f(program.u_LightColor1, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightPosition2, g, h, i);
    gl.uniform3f(program.u_LightColor2, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightPosition3, j, k, l);
    gl.uniform3f(program.u_LightColor3, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_AmbientLight, 0.2, 0.2, 0.2);
  }
}

//initialize Cubes Data
function initCube(gl) {
    var o = new Object();
    var vertices = new Float32Array([   // Vertex coordinates
       1.0, 1.0, 1.0,  -1.0, 1.0, 1.0,  -1.0,-1.0, 1.0,   1.0,-1.0, 1.0,
       1.0, 1.0, 1.0,   1.0,-1.0, 1.0,   1.0,-1.0,-1.0,   1.0, 1.0,-1.0,
       1.0, 1.0, 1.0,   1.0, 1.0,-1.0,  -1.0, 1.0,-1.0,  -1.0, 1.0, 1.0,
      -1.0, 1.0, 1.0,  -1.0, 1.0,-1.0,  -1.0,-1.0,-1.0,  -1.0,-1.0, 1.0,
      -1.0,-1.0,-1.0,   1.0,-1.0,-1.0,   1.0,-1.0, 1.0,  -1.0,-1.0, 1.0,
       1.0,-1.0,-1.0,  -1.0,-1.0,-1.0,  -1.0, 1.0,-1.0,   1.0, 1.0,-1.0
    ]);
    var normals = new Float32Array([   // Normal
       0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
       1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
       0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
      -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,
       0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,
       0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0
    ]);
    var colors = new Float32Array([     // Colors
      1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,//Red
      0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,  0.0, 1.0, 0.0,//Green
      1.0, 1.0, 1.0,  1.0, 1.0, 1.0,  1.0, 1.0, 1.0,  1.0, 1.0, 1.0,//White
      0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,  0.0, 0.0, 1.0,//Blue
      1.0, 1.0, 0.0,  1.0, 1.0, 0.0,  1.0, 1.0, 0.0,  1.0, 1.0, 0.0,//Yellow
      1.0, 0.65, 0.0,  1.0, 0.65, 0.0,  1.0, 0.65, 0.0,  1.0, 0.65, 0.0//Orange
    ]);
    var texCoords = new Float32Array([   // Texture coordinates
       1.0, 1.0,   0.0, 1.0,   0.0, 0.0,   1.0, 0.0,    // v0-v1-v2-v3 front
       0.0, 1.0,   0.0, 0.0,   1.0, 0.0,   1.0, 1.0,    // v0-v3-v4-v5 right
       1.0, 0.0,   1.0, 1.0,   0.0, 1.0,   0.0, 0.0,    // v0-v5-v6-v1 up
       1.0, 1.0,   0.0, 1.0,   0.0, 0.0,   1.0, 0.0,    // v1-v6-v7-v2 left
       0.0, 0.0,   1.0, 0.0,   1.0, 1.0,   0.0, 1.0,    // v7-v4-v3-v2 down
       0.0, 0.0,   1.0, 0.0,   1.0, 1.0,   0.0, 1.0     // v4-v7-v6-v5 back
    ]);
    var indices = new Uint8Array([        // Indices of the vertices
       0, 1, 2,   0, 2, 3,    // front
       4, 5, 6,   4, 6, 7,    // right
       8, 9,10,   8,10,11,    // up
      12,13,14,  12,14,15,    // left
      16,17,18,  16,18,19,    // down
      20,21,22,  20,22,23     // back
    ]);

    o.colors = colors;
    o.vertexBuffer = initLBuffer(gl, vertices, 3, gl.FLOAT);
    o.normalBuffer = initArrayBufferForLaterUse(gl, normals, 3, gl.FLOAT);
    o.texCoordBuffer = initArrayBufferForLaterUse(gl, texCoords, 2, gl.FLOAT);
    o.indexBuffer = initElementArrayBufferForLaterUse(gl, indices, gl.UNSIGNED_BYTE);
    o.colorBuffer = initLBuffer(gl, colors, 3, gl.FLOAT);
    o.numIndices = indices.length;
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
    return o;
}

//Builds array of cubes to be transformed.
function buildArray(side) {
  var scanValue = 2.0625;
  var dim;
  console.log("Side: ", side);
  if (side % 4 < 2) {
    scanValue = scanValue * -1;
  }


  if ((side == 0)||(side == 1)||(side == 2)||(side == 3)) {dim = 0;}
  else if ((side == 4)||(side == 5)||(side == 6)||(side == 7)) {dim = 1;}
  else {dim = 2;}

  for (var i = 0; i < cubes.length; i++) {
    switch (dim) {
      case 0:{if (cubes[i].x == scanValue) {rotate.push(i);}break;}
      case 1:{if (cubes[i].y == scanValue) {rotate.push(i);}break;}
      case 2:{if (cubes[i].z == scanValue) {rotate.push(i);}break;}
    }
  }
  console.log("Rotate Array:");
  for (var i = 0; i < rotate.length; i++) {
    console.log(rotate[i]);
  }
  translate_rotate_translate(side, dim);
  rotate.length = 0;
  return;
}

//Performs transformations on selected cubes.
function translate_rotate_translate(side, dim) {
  console.log("Dim: ", dim);
  var direction = side % 2;
  var number = 1;
  var rotation = 90;
  if (direction == 1) {rotation = 0 - rotation;}
  if (direction == 1) {number += 2;}
  console.log(rotation);
  for (var i = 0; i < rotate.length; i++) {
    for (var times = 0; times < number; times++) {
      var q = rotate[i];
      var x, y, z, u, v, w, rx, ry, rz;
      x = cubes[q].x;
      y = cubes[q].y;
      z = cubes[q].z;
      var tx = 0, ty = 0, tz = 0;
      if (x != 0) {tx = 0 - x;}
      if (y != 0) {ty = 0 - y};
      if (z != 0) {tz = 0 - z};
      cubes[q].mMatrix.translate(tx, ty, tz);
      switch (dim) {
        case 0:{
          cubes[q].u = cubes[q].u + rotation;
          if(cubes[q].u>=360) {cubes[q].u = cubes[q].u % 360;}
          else if(cubes[q].u<0) {cubes[q].u = 360+cubes[q].u;}
          cubes[q].mMatrix.rotate(0.0, rotation, 0.0, 1.0);
          break;}
        case 1:{
          cubes[q].v = cubes[q].v + rotation;
          if(cubes[q].v>=360) {cubes[q].v = cubes[q].v % 360;}
          if(cubes[q].v<0) {cubes[q].v = 360+cubes[q].v;}
          cubes[q].mMatrix.rotate(0.0, 0.0, rotation, 1.0); break;}
        case 2:{
          cubes[q].w = cubes[q].w + rotation;
          if(cubes[q].w>=360) {cubes[q].w = cubes[q].w % 360;}
          if(cubes[q].w<0) {cubes[q].w = 360+cubes[q].w;}
          cubes[q].mMatrix.rotate(rotation, 0.0, 0.0, 1.0);
          break;}
      }
      switch (dim) {
        case 0: {
          u = x;
          if (y > 0) {
            if (z > 0) {v = y;}
            else if (z == 0) {v = 0;}
            else {v = 0 - y;}
            w = -2.0625;}
          else if (y < 0) {
            if (z > 0) {v = 0-y;}
            else if (z == 0) {v = 0;}
            else {v = y;}
            w = 2.0625;}
          else if ((y == 0)&&(z == 0)) {u=x;v=y;w=z;}
          else {
            if (z > 0) {v = 2.0625;}
            else {v = -2.0625;}
            w = 0;
          }
          break;
        }
        case 1: {
          v = y;
          if (x > 0) {
            if (z > 0) {u = x;}
            else if (z == 0) {u = 0;}
            else {u = 0 - x;}
            w = -2.0625;}
          else if (x < 0) {
            if (z > 0) {u = 0-x;}
            else if (z == 0) {u = 0;}
            else {u = x;}
            w = 2.0625;}
          else if ((x == 0)&&(z == 0)) {u=x;v=y;w=z;}
          else {
            if (z > 0) {u = 2.0625;}
            else {u = -2.0625;}
            w = 0;
          }
          break;
        }
        case 2: {
          w = z;
          if (x > 0) {
            if (y > 0) {u = x;}
            else if (y == 0) {u = 0;}
            else {u = 0 - x;}
            v = -2.0625;}
          else if (x < 0) {
            if (y > 0) {u = 0-x;}
            else if (y == 0) {u = 0;}
            else {u = x;}
            v = 2.0625;}
          else if ((x == 0)&&(y == 0)) {u=x;v=y;w=z;}
          else {
            if (y > 0) {u = 2.0625;}
            else {u = -2.0625;}
            v = 0;
          }
          break;
        }
      }
      cubes[q].mMatrix.translate(u, v, w);
      cubes[q].x = u;
      cubes[q].y = v;
      cubes[q].z = w;
    }
  }
  return;
}


//Logic to turn left.
function turnLeft() {
    if (ang <= 0) {ang = 357;}
    else {ang = (ang -3);}
    if(aZ < gZ && aX > gX) {aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));}
    else if (aZ < gZ && aX <= gX) {aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));}
    else if (aZ >= gZ && aX > gX) {aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));}
    else if (aZ >= gZ && aX <= gX) {aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));}
    else {return;}
}
//Reverse direction logic.
function reverse() {
    rZ = gZ - mC(dTr((ang+180)%360));rX = gX + mS(dTr((ang+180)%360));
    gZ = rZ;gX = rX;aZ = gZ - mC(dTr(ang));aX = gX + mS(dTr(ang));
}
//Degrees to Radians
function dTr (rads) {return rads * (Math.PI/180);}
//Math.cos
function mC (ang) {return Math.cos(ang);}
//Math.sin
function mS (ang) {return Math.sin(ang);}
//Process keydown events.
function keydown(ev) {
  console.log(ev.keyCode);
  switch (ev.keyCode) {
    case 37:turnLeft();break;
    case 38:gZ = aZ;gX = aX;aZ = gZ - mC(dTr(ang));aX = gX + mS(dTr(ang));break;
    case 39:ang = (ang + 3)%360;aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));break;
    case 40:reverse();break;
    case 65:buildArray(0);break;//A
    case 66:buildArray(1);break;//B
    case 67:buildArray(2);break;//C
    case 68:buildArray(3);break;//D
    case 69:buildArray(4);break;//E
    case 70:buildArray(5);break;//F
    case 71:buildArray(6);break;//G
    case 72:buildArray(7);break;//H
    case 73:buildArray(8);break;//I
    case 74:buildArray(9);break;//J
    case 75:buildArray(10);break;//K
    case 76:buildArray(11);break;//L
    default:break;
  }
}

function initArrayBuffer(gl, program, attribute, data, type, num) {
  gl.useProgram(program);
  var buffer = gl.createBuffer();
  if (!buffer) {console.log('Failed buffer');return false;}
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  var a_attribute = gl.getAttribLocation(program, attribute);
  if (a_attribute < 0) {console.log('Failed store ' + attribute);return false;}
  gl.vertexAttribPointer(a_attribute, num, type, false, 0, 0);
  gl.enableVertexAttribArray(a_attribute);
  return true;
}

//Set light locations.
function lC() {a = -3;b = 3;c = -3;d = 3; e = 3;f = -3;g = -3;h = -3;i = 3;j = 3; k = -3;l = 3;}
