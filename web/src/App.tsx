import './App.css';
import { useAuth } from '@/auth/AuthProvider';
import { useNavigate } from 'react-router';
import { useEffect } from 'react';

function App() {
  const { user } = useAuth();
  const navigate = useNavigate();

  useEffect(() => {
    if (user) {
      navigate('/dashboard');
    } else {
      navigate('/login');
    }
  }, [user, navigate]);

  return (
    <div className="flex justify-center items-center h-screen ">
      Redirecting...
    </div>
  );
}

export default App;
