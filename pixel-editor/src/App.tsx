import { useEffect, useRef, useState } from "react";
// import Editor from "./components/Editor.jsx";

function App() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [dibujando, setDibujando] = useState(false);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    canvas.width = window.innerWidth - 20;
    canvas.height = window.innerHeight - 20;
    
  }, []);

  const evtInicioDibuja = () => {
    setDibujando(true);
  }

  const evtFinDibuja = () => {
    setDibujando(false);
  }

  const evtDibujaCanvas = (evt: React.MouseEvent) => {
    if (!dibujando) return;
    const canvas = canvasRef.current;
    if (!canvas) return;  

    const ctx = canvas.getContext('2d');
    if (!ctx) return;
    
    const rect = canvas.getBoundingClientRect();
    const x = evt.clientX - rect.left;
    const y = evt.clientY - rect.top;
    
    ctx.fillStyle = 'White';
    ctx.fillRect(x, y, 5, 5);
  }

  return (
    <canvas
    ref = {canvasRef}
    style =  {{ border: '1px solid black', backgroundColor: 'teal'}}
    onMouseDown={evtInicioDibuja}
    onMouseMove = {evtDibujaCanvas}
    onMouseUp={evtFinDibuja}
    />

    // <>
    //   <Editor />
    // </>
  )
}

export default App
