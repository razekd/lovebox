import { useState, useEffect } from 'react';
import {
  Form,
  FormControl,
  FormField,
  FormItem,
  FormLabel,
  FormMessage,
} from '@/components/ui/form';
import { Card, CardHeader } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Alert, AlertDescription } from '@/components/ui/alert';
import { AlertCircle } from 'lucide-react';

import { zodResolver } from '@hookform/resolvers/zod';
import { useForm } from 'react-hook-form';
import { z } from 'zod';

import { useAuth } from '@/auth/AuthProvider';
import { useNavigate } from 'react-router';

const formSchema = z.object({
  username: z.enum(['david', 'angelique'], {
    errorMap: () => ({ message: 'Please select a username.' }),
  }),
  password: z.string().min(4, {
    message: 'Password must be at least 4 characters.',
  }),
});

const LoginPage = () => {
  const { user, login } = useAuth();
  const [error, setError] = useState('');
  const [isLoading, setIsLoading] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    if (user) {
      navigate('/dashboard', { replace: true });
    }
  }, [user, navigate]);

  const handleLogin = async (username: string, password: string) => {
    try {
      setError('');
      setIsLoading(true);

      if (!username || !password) {
        setError('Please fill in all fields');
        return;
      }

      await login(username, password);
      navigate('/dashboard');
    } catch (err) {
      setError('Login failed. Please check your credentials.');
    } finally {
      setIsLoading(false);
    }
  };

  const onSubmit = async (data: z.infer<typeof formSchema>) => {
    await handleLogin(data.username, data.password);
  };

  const form = useForm<z.infer<typeof formSchema>>({
    resolver: zodResolver(formSchema),
    defaultValues: {
      username: undefined,
      password: '',
    },
  });

  const selectUsername = (username: 'david' | 'angelique') => {
    form.setValue('username', username);
    // Clear error when user makes a selection
    if (error) setError('');
  };

  if (user) {
    return (
      <div className="flex justify-center items-center h-screen">
        Redirecting...
      </div>
    );
  }

  return (
    <Card className="max-w-md mx-10 sm:mx-auto mt-10 p-6">
      <CardHeader className="text-center">
        <h2 className="text-2xl font-bold">Login to your dashboard</h2>
      </CardHeader>

      {error && (
        <Alert className="border-red-200 bg-red-50 mb-4">
          <AlertCircle className="h-4 w-4 text-red-600" />
          <AlertDescription className="text-red-800">{error}</AlertDescription>
        </Alert>
      )}

      <Form {...form}>
        <form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
          <FormField
            control={form.control}
            name="username"
            render={({ field }) => (
              <FormItem>
                <FormLabel>Select User</FormLabel>
                <FormControl>
                  <div className="flex space-x-2">
                    <Button
                      type="button"
                      variant={field.value === 'david' ? 'default' : 'outline'}
                      onClick={() => selectUsername('david')}
                      className={
                        field.value === 'david'
                          ? 'cursor-not-allowed'
                          : 'cursor-pointer'
                      }
                      disabled={isLoading}
                    >
                      David
                    </Button>
                    <Button
                      type="button"
                      variant={
                        field.value === 'angelique' ? 'default' : 'outline'
                      }
                      onClick={() => selectUsername('angelique')}
                      className={
                        field.value === 'angelique'
                          ? 'cursor-not-allowed'
                          : 'cursor-pointer'
                      }
                      disabled={isLoading}
                    >
                      Angélique
                    </Button>
                  </div>
                </FormControl>
                <FormMessage />
              </FormItem>
            )}
          />
          <FormField
            control={form.control}
            name="password"
            render={({ field }) => (
              <FormItem>
                <FormLabel>Password</FormLabel>
                <FormControl>
                  <Input
                    type="password"
                    placeholder="Enter your password"
                    disabled={isLoading}
                    {...field}
                    onChange={(e) => {
                      field.onChange(e);
                      // Clear error when user starts typing
                      if (error) setError('');
                    }}
                  />
                </FormControl>
                <FormMessage />
              </FormItem>
            )}
          />
          <Button
            type="submit"
            className="cursor-pointer w-full"
            disabled={isLoading}
          >
            {isLoading ? 'Logging in...' : 'Login'}
          </Button>
        </form>
      </Form>
    </Card>
  );
};

export default LoginPage;
