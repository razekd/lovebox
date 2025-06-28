import { Card, CardDescription, CardHeader } from './ui/card';
import { Button } from './ui/button';
import { useAuth } from '@/auth/AuthProvider';
import { useNavigate } from 'react-router';

const LogoutForm = () => {
  const navigate = useNavigate();
  const { logout } = useAuth();
  const handleLogOut = () => {
    logout();
    navigate('/login');
  };
  return (
    <Card className="w-full px-6 gap-0">
      <CardHeader className="px-0">
        <CardDescription>
          Finished ? Click the button below to log out.
        </CardDescription>
      </CardHeader>
      <Button
        className="w-full cursor-pointer"
        variant="outline"
        onClick={handleLogOut}
      >
        Logout
      </Button>
    </Card>
  );
};
export default LogoutForm;
