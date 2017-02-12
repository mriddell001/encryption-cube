//Vertex Shader For Solid Cubes
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
'uniform vec3 u_AmbientLight;\n' +
'varying vec3 v_Normal;\n' +
'varying vec3 v_Position;\n' +
'varying vec4 v_Color;\n' +
'void main() {\n' +
'  vec3 normal = normalize(v_Normal);\n' +
'  vec3 lightDirection0 = normalize(u_LightPosition0 - v_Position);\n' +
'  vec3 lightDirection1 = normalize(u_LightPosition1 - v_Position);\n' +
'  float nDotL0 = max(dot(lightDirection0, normal), 0.0);\n' +
'  float nDotL1 = max(dot(lightDirection1, normal), 0.0);\n' +
'  vec3 diffuse0 = u_LightColor0 * v_Color.rgb * nDotL0;\n' +
'  vec3 diffuse1 = u_LightColor1 * v_Color.rgb * nDotL1;\n' +
'  vec3 ambient = u_AmbientLight * v_Color.rgb;\n' +
'  vec4 color0 = vec4(diffuse0 + ambient, v_Color.a);\n' +
'  vec4 color1 = vec4(diffuse1 + ambient, v_Color.a);\n' +
'  gl_FragColor = color0 + color1;\n' +
'}\n';

//Vertex Shader For Solid Spheres
var SPHERE_V_SOURCE =
'attribute vec4 a_Position;\n' +
'attribute vec4 a_Normal;\n' +
'uniform mat4 u_MvpMatrix;\n' +
'uniform mat4 u_ModelMatrix;\n' +    // Model matrix
'uniform mat4 u_NormalMatrix;\n' +   // Transformation matrix of the normal
'varying vec4 v_Color;\n' +
'varying vec3 v_Normal;\n' +
'varying vec3 v_Position;\n' +
'void main() {\n' +
'  vec4 color = vec4(1.0, 0.0, 0.0, 1.0);\n' + // Sphere color
'  gl_Position = u_MvpMatrix * a_Position;\n' +
'  v_Position = vec3(u_ModelMatrix * a_Position);\n' +
'  v_Normal = normalize(vec3(u_NormalMatrix * a_Normal));\n' +
'  v_Color = color;\n' +
'}\n';

//Fragment Shader For Solid Spheres
var SPHERE_F_SOURCE =
'#ifdef GL_ES\n' +
'precision mediump float;\n' +
'#endif\n' +
'uniform vec3 u_LightColor0;\n' +
'uniform vec3 u_LightPosition0;\n' +
'uniform vec3 u_LightColor1;\n' +
'uniform vec3 u_LightPosition1;\n' +
'uniform vec3 u_AmbientLight;\n' +
'varying vec3 v_Normal;\n' +
'varying vec3 v_Position;\n' +
'varying vec4 v_Color;\n' +
'void main() {\n' +
'  vec3 normal = normalize(v_Normal);\n' +
'  vec3 lightDirection0 = normalize(u_LightPosition0 - v_Position);\n' +
'  vec3 lightDirection1 = normalize(u_LightPosition1 - v_Position);\n' +
'  float nDotL0 = max(dot(lightDirection0, normal), 0.0);\n' +
'  float nDotL1 = max(dot(lightDirection1, normal), 0.0);\n' +
'  vec3 diffuse0 = u_LightColor0 * v_Color.rgb * nDotL0;\n' +
'  vec3 diffuse1 = u_LightColor1 * v_Color.rgb * nDotL1;\n' +
'  vec3 ambient = u_AmbientLight * v_Color.rgb;\n' +
'  vec4 color0 = vec4(diffuse0 + ambient, v_Color.a);\n' +
'  vec4 color1 = vec4(diffuse1 + ambient, v_Color.a);\n' +
'  gl_FragColor = color0 + color1;\n' +
'}\n';

//Vertex Shader for Texture Program
var T_VSHD_SRC =
'#ifdef GL_ES\n' +
'precision mediump float;\n' +
'#endif\n' +
'attribute vec4 a_Position;\n' +
'attribute vec4 a_Normal;\n' +
'attribute vec2 a_TexCoord;\n' +
'uniform mat4 u_MvpMatrix;\n' +
'uniform mat4 u_NormalMatrix;\n' +
'varying float v_NdotL;\n' +
'varying vec2 v_TexCoord;\n' +
'void main() {\n' +
'  gl_Position = u_MvpMatrix * a_Position;\n' +
'  vec3 normal = normalize(vec3(u_NormalMatrix * a_Normal));\n' +
'  vec3 identity = vec3(1.0, 1.0, 1.0);\n' +
'  v_NdotL = max(dot(normal, identity), 0.0);\n' +
'  v_TexCoord = a_TexCoord;\n' +
'}\n';

//Fragment Shader for Texture Program
var T_FSHD_SRC =
'#ifdef GL_ES\n' +
'precision mediump float;\n' +
'#endif\n' +
'uniform sampler2D u_Sampler;\n' +
'varying vec2 v_TexCoord;\n' +
'varying float v_NdotL;\n' +
'void main() {\n' +
'  vec4 color = texture2D(u_Sampler, v_TexCoord);\n' +
'  gl_FragColor = vec4(color.rgb * v_NdotL, color.a);\n' +
'}\n';

var gX = 0, gY = 2, gZ = 5;
var ang = 0, aX = 0, aY = 2, aZ = 4;
var g_last = Date.now();

var a, b, c, d, e, f;
var cubes = [];
var spheres = [];
var ca = [];
var texture_loaded = false;
var texture;
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
    ca[0] = makeColors(0.39,0.26,0.13);
    ca[1] = makeColors(0.37,0.24,0.11);
    ca[2] = makeColors(0.0,0.0,0.0);
    cubes[0] = {mMatrix:new Matrix4()};
    cubes[1] = {mMatrix:new Matrix4()};
    cubes[2] = {mMatrix:new Matrix4()};
    cubes[3] = {mMatrix:new Matrix4()};
    cubes[4] = {mMatrix:new Matrix4()};
    cubes[5] = {mMatrix:new Matrix4()};
    cubes[6] = {mMatrix:new Matrix4()};
    cubes[7] = {mMatrix:new Matrix4()};
    spheres[0] = {mMatrix:new Matrix4()};
    spheres[1] = {mMatrix:new Matrix4()};
    spheres[2] = {mMatrix:new Matrix4()};
    var canvas = document.getElementById('webgl');
    var gl = getWebGLContext(canvas);
    if (!gl) {console.log('Failed WebgL');return;}

    var tProg = createProgram(gl, T_VSHD_SRC, T_FSHD_SRC);
    var sProg = createProgram(gl, S_VSHD_SRC, S_FSHD_SRC);
    var xProg = createProgram(gl, SPHERE_V_SOURCE, SPHERE_F_SOURCE);
    initProgram(gl, tProg, 1);
    initProgram(gl, sProg, 0);
    texture = gl.createTexture();
    var Cube = initCube(gl);

    setStage(gl, sProg);
    m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
    m.pMatrix.setPerspective(90, canvas.width/canvas.height, 0.1, 100);
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(m.mMatrix);

    gl.clearColor(1.0, 1.0, 1.0, 1.0);
    gl.enable(gl.DEPTH_TEST);
    gl.clear(gl.COLOR_BUFFER_BIT);

    if (!initTextures(gl, tProg, Cube)) {console.log('Failed texture.');return;}

    document.onkeydown = function(ev){
      keydown(ev);};

    var tick = function() {
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        drawTextureCube(gl, Cube, tProg);
        drawCube(gl, Cube, sProg);
        initSphere(gl, xProg, canvas);
        requestAnimationFrame(tick);
    };
    tick();
}

//Draw Cube Ojbects
function drawCube(gl, o, program) {
    gl.useProgram(program);
    if (lights == true) {
      gl.uniform3f(program.u_LightColor0, 0.8, 0.8, 0.8);
      gl.uniform3f(program.u_LightColor1, 0.8, 0.8, 0.8);}
    else {
      gl.uniform3f(program.u_LightColor0, 0.0, 0.0, 0.0);
      gl.uniform3f(program.u_LightColor1, 0.0, 0.0, 0.0);}
    initAttributeVariable(gl, program.a_Position, o.vertexBuffer);
    initAttributeVariable(gl, program.a_Normal, o.normalBuffer);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, o.indexBuffer);
    m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(m.mMatrix);
    for (var i = 1; i < cubes.length; i++) {
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

//Draw Textured Objects
function drawTextureCube(gl, o, program, i) {
    gl.useProgram(program);
    initAttributeVariable(gl, program.a_Position, o.vertexBuffer);
    initAttributeVariable(gl, program.a_Normal, o.normalBuffer);
    initAttributeVariable(gl, program.a_TexCoord, o.texCoordBuffer);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, o.indexBuffer);
    m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(m.mMatrix);

    if (texture_loaded == true) {
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture);
      m.nMatrix.setInverseOf(cubes[0].mMatrix);
      m.nMatrix.transpose();
      gl.uniformMatrix4fv(program.u_NormalMatrix, false, m.nMatrix.elements);
      m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(cubes[0].mMatrix);
      gl.uniformMatrix4fv(program.u_MvpMatrix, false, m.mvpMatrix.elements);
      gl.uniform1i(program.u_Sampler, 0);
      gl.drawElements(gl.TRIANGLES, o.numIndices, o.indexBuffer.type, 0);
      gl.bindBuffer(gl.ARRAY_BUFFER, null);
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
      gl.bindTexture(gl.TEXTURE_2D, null);
    }
}

//Initialize Textures
function initTextures(gl, program, o) {
    gl.useProgram(program);
    var img = new Image();
    img.onload = function(){
      gl.useProgram(program);
      gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture);
      gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.REPEAT);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.REPEAT);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      gl.uniform1i(program.u_Sampler, 0);
      gl.bindTexture(gl.TEXTURE_2D, null);
      texture_loaded = true;
    };
    img.src = './floor.jpg';
    return true;
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
    case 1:o.colorBuffer = initLBuffer(gl, ca[0], 3, gl.FLOAT);break;
    case 2:o.colorBuffer = initLBuffer(gl, ca[1], 3, gl.FLOAT);break;
    case 3:o.colorBuffer = initLBuffer(gl, ca[2], 3, gl.FLOAT);break;
    case 4:o.colorBuffer = initLBuffer(gl, o.colors, 3, gl.FLOAT);break;
    default:o.colorBuffer = initLBuffer(gl, ca[0], 3, gl.FLOAT);break;
  }
  initAttributeVariable(gl, program.a_Color, o.colorBuffer);
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, o.indexBuffer);
}

//Set the position, scale, and rotation of all objects in scene.
function setStage(gl, program) {
  var r, s, t, u, v, w, x, y, z;
  for (var i = 0; i < spheres.length; i++) {
    switch (i) {
      case 0:u = -0.3; v = 1.5; w = -4; x = y = z = 0.0;break;
      default:
        if(i == 1) {u=a;v=b;w=c;}else{u=d;v=e;w=f;}x=y=z=0.0;
    }
    spheres[i].mMatrix.translate(u, v, w);spheres[i].mMatrix.scale(x, y, z);
  }
  for (var i = 0; i < cubes.length; i++) {
    switch (i) {
      case 0:r=0;s=0;t=0;u=0;v=-2;w=0;x=20;y=0.1;z=20;break;
      case 1:r=0;s=0;t=0;u=0;u=0;v=4.5;w=-7;x=10;y=5;z=0.1;break;
      case 2:r=0;s=0;t=0;u=0;u=0;v=-0.8;w=-4.1;x=10;y=0.5;z=3;break;
      case 3:r=0;s=0;t=0;u=0;u=0;v=-10;w=0;x=y=z=20;break;
      case 4:r=45;s=45;t=45;u=45;u = 0; v = 1.5; w = -4; x = y = z = 1;break;
      case 5:r=0;s=0;t=0;u=0;u = 9.9; v = 9.25; w = -4; x = y = 0.25;z = 3;break;
      case 6:r=0;s=0;t=0;u=0;u = -9.9; v = 9.25; w = -4; x = y = 0.25;z = 3;break;
      case 7:r=0;s=0;t=0;u=0;u = 0; v = 9.25; w = -1; z = y = 0.25;x = 10.1;break;
      default:
    }
    cubes[i].mMatrix.translate(u, v, w);
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
  if (i) {
    program.a_TexCoord = gl.getAttribLocation(program, 'a_TexCoord');
    program.u_Sampler = gl.getUniformLocation(program, 'u_Sampler');
  }
  else {
    program.a_Color = gl.getAttribLocation(program, 'a_Color');
    program.u_ModelMatrix = gl.getUniformLocation(program, 'u_ModelMatrix');
    program.u_LightColor0 = gl.getUniformLocation(program, 'u_LightColor0');
    program.u_LightPosition0 = gl.getUniformLocation(program, 'u_LightPosition0');
    program.u_LightColor1 = gl.getUniformLocation(program, 'u_LightColor1');
    program.u_LightPosition1 = gl.getUniformLocation(program, 'u_LightPosition1');
    program.u_AmbientLight = gl.getUniformLocation(program, 'u_AmbientLight');
    gl.uniform3f(program.u_LightPosition0, a, b, c);
    gl.uniform3f(program.u_LightColor0, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightColor1, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightPosition1, d, e, f);
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
      0.4, 0.4, 1.0,  0.4, 0.4, 1.0,  0.4, 0.4, 1.0,  0.4, 0.4, 1.0,
      0.4, 1.0, 0.4,  0.4, 1.0, 0.4,  0.4, 1.0, 0.4,  0.4, 1.0, 0.4,
      1.0, 0.4, 0.4,  1.0, 0.4, 0.4,  1.0, 0.4, 0.4,  1.0, 0.4, 0.4,
      1.0, 1.0, 0.4,  1.0, 1.0, 0.4,  1.0, 1.0, 0.4,  1.0, 1.0, 0.4,
      1.0, 1.0, 1.0,  1.0, 1.0, 1.0,  1.0, 1.0, 1.0,  1.0, 1.0, 1.0,
      0.4, 1.0, 1.0,  0.4, 1.0, 1.0,  0.4, 1.0, 1.0,  0.4, 1.0, 1.0
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
//Create color arrays for cubes.
function makeColors(a, b, c) {
  var ca = new Array();
  for (var i = 0; i < 24; i++) {ca.push(a);ca.push(b);ca.push(c);}
  var color = new Float32Array(ca);
  return color;
}
//Process keydown events.
function keydown(ev) {
  switch (ev.keyCode) {
    /*case 37:turnLeft();break;
    case 38:gZ = aZ;gX = aX;aZ = gZ - mC(dTr(ang));aX = gX + mS(dTr(ang));break;
    case 39:ang = (ang + 3)%360;aZ=(gZ-mC(dTr(ang)));aX=(gX+mS(dTr(ang)));break;
    case 40:reverse();break;*/
    case 49:break;
    case 50:break;
    /*case 76:console.log("aX: " + aX + " aZ: " + aZ + " gX: " + gX + " gZ: " + gZ + "ang: " + ang);break;
    case 87:if(lights == true){lights = false;}else{lights = true;}break;*/
    default:break;
  }
}
//All inclusive sphere creation function.
function initSphere(gl, program, canvas) {
  gl.useProgram(program);
  var n = initVertexBuffers(gl, program);
  if (prime == true) {
    gl.useProgram(program);
    program.u_ModelMatrix = gl.getUniformLocation(program, 'u_ModelMatrix');
    program.u_MvpMatrix = gl.getUniformLocation(program, 'u_MvpMatrix');
    program.u_NormalMatrix = gl.getUniformLocation(program, 'u_NormalMatrix');
    program.u_LightColor0 = gl.getUniformLocation(program, 'u_LightColor0');
    program.u_LightPosition0 = gl.getUniformLocation(program, 'u_LightPosition0');
    program.u_LightColor1 = gl.getUniformLocation(program, 'u_LightColor1');
    program.u_LightPosition1 = gl.getUniformLocation(program, 'u_LightPosition1');
    program.u_AmbientLight = gl.getUniformLocation(program, 'u_AmbientLight');
    prime = false;
    gl.uniform3f(program.u_AmbientLight, 0.2, 0.2, 0.2);
    gl.uniform3f(program.u_LightPosition0, a, b, c);
    gl.uniform3f(program.u_LightPosition1, d, e, f);
  }
  if (lights == true) {
    gl.uniform3f(program.u_LightColor0, 0.8, 0.8, 0.8);
    gl.uniform3f(program.u_LightColor1, 0.8, 0.8, 0.8);}
  else {
    gl.uniform3f(program.u_LightColor0, 0.0, 0.0, 0.0);
    gl.uniform3f(program.u_LightColor1, 0.0, 0.0, 0.0);}
  m.vMatrix.setLookAt(gX, gY, gZ, aX, aY, aZ, 0, 1, 0);
  for (var i = 0; i < 3; i++) {
    m.mvpMatrix.set(m.pMatrix).multiply(m.vMatrix).multiply(spheres[i].mMatrix);
    m.nMatrix.setInverseOf(spheres[i].mMatrix);
    m.nMatrix.transpose();

    gl.uniformMatrix4fv(program.u_ModelMatrix, false, spheres[i].mMatrix.elements);
    gl.uniformMatrix4fv(program.u_MvpMatrix, false, m.mvpMatrix.elements);
    gl.uniformMatrix4fv(program.u_NormalMatrix, false, m.nMatrix.elements);
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_SHORT, 0);
  }
  gl.bindBuffer(gl.ARRAY_BUFFER, null);
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
}
//Initialize Sphere data
function initVertexBuffers(gl, program) { // Create a sphere
  var SPHERE_DIV = 13;
  var i, ai, si, ci;
  var j, aj, sj, cj;
  var p1, p2;
  var positions = [];
  var indices = [];

  for (j = 0; j <= SPHERE_DIV; j++) {
    aj = j * Math.PI / SPHERE_DIV;
    sj = Math.sin(aj);
    cj = Math.cos(aj);
    for (i = 0; i <= SPHERE_DIV; i++) {
      ai = i * 2 * Math.PI / SPHERE_DIV;
      si = Math.sin(ai);
      ci = Math.cos(ai);
      positions.push(si * sj);  // X
      positions.push(cj);       // Y
      positions.push(ci * sj);  // Z
    }
  }
  for (j = 0; j < SPHERE_DIV; j++) {
    for (i = 0; i < SPHERE_DIV; i++) {
      p1 = j * (SPHERE_DIV+1) + i;
      p2 = p1 + (SPHERE_DIV+1);
      indices.push(p1);
      indices.push(p2);
      indices.push(p1 + 1);
      indices.push(p1 + 1);
      indices.push(p2);
      indices.push(p2 + 1);
    }
  }
  if (!initArrayBuffer(gl, program, 'a_Position', new Float32Array(positions), gl.FLOAT, 3)) return -1;
  if (!initArrayBuffer(gl, program, 'a_Normal', new Float32Array(positions), gl.FLOAT, 3))  return -1;

  gl.bindBuffer(gl.ARRAY_BUFFER, null);
  var indexBuffer = gl.createBuffer();
  if (!indexBuffer) {console.log('Failed to create the buffer object');return -1;}
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

  return indices.length;
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
function lC() {a = -4;b = 6;c = -3;d = 4; e = 6;f = -3;}
